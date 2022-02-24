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

ZpaqLibrary::ZpaqLibrary() {}

ZpaqLibrary::~ZpaqLibrary() {}
