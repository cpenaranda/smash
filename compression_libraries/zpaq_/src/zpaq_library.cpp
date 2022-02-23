/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <libzpaq.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <zpaq_library.hpp>

int ZpaqReader::get() {
  char value;
  return (this->read(&value, 1)) ? static_cast<int>(value) : -1;
}

int ZpaqReader::read(char *buf, int size) {
  int real_size{0};
  if (buffer_) {
    real_size = (size > buffer_size_) ? buffer_size_ : size;
    memcpy(buf, buffer_, real_size);
    buffer_ += real_size;
    buffer_size_ -= real_size;
  }
  return real_size;
}

ZpaqReader::ZpaqReader(char *buffer, const uint64_t &buffer_size)
    : buffer_(buffer), buffer_size_(buffer_size) {}

void ZpaqWriter::put(int c) {
  char value = static_cast<char>(c);
  this->write(&value, 1);
}

void ZpaqWriter::write(const char *buf, int n) {
  if (buffer_) {
    if (n > buffer_size_) {
      std::cout << "ERROR: Zpaq error when compress data" << std::endl;
      error_ = true;
    } else {
      memcpy(buffer_, buf, n);
      buffer_ += n;
      buffer_size_ -= n;
    }
  }
}

bool ZpaqWriter::GetRealSize(uint64_t *buffer_size) {
  *buffer_size -= buffer_size_;
  return error_;
}

ZpaqWriter::ZpaqWriter(char *buffer, const uint64_t &buffer_size)
    : buffer_(buffer), buffer_size_(buffer_size), error_(false) {}

bool ZpaqLibrary::CheckOptions(const Options &options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel(
        "zpaq", options.GetCompressionLevel(), 0, 11);
  }
  return result;
}

bool ZpaqLibrary::SetOptionsCompressor(const Options &options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) options_ = options;
  return initialized_compressor_;
}

bool ZpaqLibrary::SetOptionsDecompressor(const Options &options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) options_ = options;
  return initialized_decompressor_;
}

void ZpaqLibrary::GetCompressedDataSize(char *uncompressed_data,
                                        uint64_t uncompressed_size,
                                        uint64_t *compressed_size) {
  // There is no way to obtain with Zpaq
  *compressed_size = ((uncompressed_size / 5000) + 1) * 5000;
}

bool ZpaqLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                           char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    ZpaqReader reader(uncompressed_data, uncompressed_size);
    ZpaqWriter writer(compressed_data, *compressed_size);

    char method[3];
    method[0] = '1';
    if (options_.GetCompressionLevel() > 9) {
      method[1] = '1';
      method[2] = '0' + options_.GetCompressionLevel() - 10;
    } else {
      method[1] = '0';
      method[2] = '0' + options_.GetCompressionLevel();
    }
    compress(&reader, &writer, method);
    if (writer.GetRealSize(compressed_size)) {
      std::cout << "ERROR: zpaq error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void ZpaqLibrary::GetDecompressedDataSize(char *compressed_data,
                                          uint64_t compressed_size,
                                          uint64_t *decompressed_size) {
  // There is no way to obtain with Zpaq
}

bool ZpaqLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                             char *decompressed_data,
                             uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    ZpaqReader reader(compressed_data, compressed_size);
    ZpaqWriter writer(decompressed_data, *decompressed_size);
    decompress(&reader, &writer);
    if (writer.GetRealSize(decompressed_size)) {
      std::cout << "ERROR: zpaq error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void ZpaqLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "zpaq",
      "A journaling archiver optimized for user-level incremental backup of "
      "directory trees in Windows and *nix");
}

bool ZpaqLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 11;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [0-11]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool ZpaqLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool ZpaqLibrary::GetModeInformation(std::vector<std::string> *mode_information,
                                     uint8_t *minimum_mode,
                                     uint8_t *maximum_mode,
                                     const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
  return false;
}

bool ZpaqLibrary::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool ZpaqLibrary::GetShuffleInformation(
    std::vector<std::string> *shuffle_information, uint8_t *minimum_shuffle,
    uint8_t *maximum_shuffle) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
  return false;
}

bool ZpaqLibrary::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

std::string ZpaqLibrary::GetModeName(const uint8_t &mode) {
  return CompressionLibrary::GetDefaultModeName();
}

std::string ZpaqLibrary::GetShuffleName(const uint8_t &shuffle) {
  return CompressionLibrary::GetDefaultShuffleName();
}

ZpaqLibrary::ZpaqLibrary() {}

ZpaqLibrary::~ZpaqLibrary() {}
