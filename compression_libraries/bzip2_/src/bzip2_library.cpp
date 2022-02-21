/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <bzlib.h>

// SMASH LIBRARIES
#include <bzip2_library.hpp>
#include <options.hpp>

bool Bzip2Library::CheckOptions(const Options &options,
                                const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel(
        "bzip2", options.GetCompressionLevel(), 1, 9);
    if (result) {
      result = CompressionLibrary::CheckWorkFactor(
          "bzip2", options.GetWorkFactor(), 0, 250);
    }
  } else {
    result = CompressionLibrary::CheckMode("bzip2", options.GetMode(), 0, 1);
  }
  return result;
}

bool Bzip2Library::SetOptionsCompressor(const Options &options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) options_ = options;
  return initialized_compressor_;
}

bool Bzip2Library::SetOptionsDecompressor(const Options &options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) options_ = options;
  return initialized_decompressor_;
}

void Bzip2Library::GetCompressedDataSize(uint64_t uncompressed_size,
                                         uint64_t *compressed_size) {
  // There is no way to obtain with Bzip2
  *compressed_size = ((uncompressed_size / 5000) + 1) * 5000;
}

bool Bzip2Library::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                            char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    int bzerr = BZ2_bzBuffToBuffCompress(
        compressed_data, reinterpret_cast<uint32_t *>(compressed_size),
        uncompressed_data, static_cast<uint32_t>(uncompressed_size),
        options_.GetCompressionLevel(), 0 /* verbosity */,
        options_.GetWorkFactor());
    if (bzerr != BZ_OK && bzerr != BZ_OUTBUFF_FULL) {
      std::cout << "ERROR: bzip2 error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool Bzip2Library::Decompress(char *compressed_data, uint64_t compressed_size,
                              char *decompressed_data,
                              uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    int bzerr = BZ2_bzBuffToBuffDecompress(
        decompressed_data, reinterpret_cast<uint32_t *>(decompressed_size),
        compressed_data, static_cast<uint32_t>(compressed_size),
        options_.GetMode(), 0 /* verbosity */);
    if (bzerr != BZ_OK) {
      std::cout << "ERROR: bzip2 error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void Bzip2Library::GetDecompressedDataSize(char *compressed_data,
                                           uint64_t compressed_size,
                                           uint64_t *decompressed_size) {
  // There is no way to obtain with Bzip2
}

void Bzip2Library::GetTitle() {
  CompressionLibrary::GetTitle(
      "bzip2", "Based on Burrows-Wheeler algorithm and Huffman coding");
}

bool Bzip2Library::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 1;
  if (maximum_level) *maximum_level = 9;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [1-9]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool Bzip2Library::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool Bzip2Library::GetModeInformation(
    std::vector<std::string> *mode_information, uint8_t *minimum_mode,
    uint8_t *maximum_mode, const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 1;
  if (mode_information) {
    mode_information->clear();
    mode_information->push_back("Available values [0-1]");
    mode_information->push_back("0: " + modes_[0] +
                                " decompression using more memory");
    mode_information->push_back("1: " + modes_[1] +
                                " decompression using less memory");
    mode_information->push_back("[decompression]");
  }
  return true;
}

bool Bzip2Library::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 250;
  if (work_factor_information) {
    work_factor_information->clear();
    work_factor_information->push_back("Available values [0-250]");
    work_factor_information->push_back(
        "Controls the compression behaviour when there is repetitive data");
    work_factor_information->push_back("[compression]");
  }
  return true;
}

bool Bzip2Library::GetShuffleInformation(
    std::vector<std::string> *shuffle_information, uint8_t *minimum_shuffle,
    uint8_t *maximum_shuffle) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
  return false;
}

bool Bzip2Library::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

std::string Bzip2Library::GetModeName(const uint8_t &mode) {
  std::string result = CompressionLibrary::GetDefaultModeName();
  if (mode < number_of_modes_) {
    result = modes_[mode];
  }
  return result;
}

std::string Bzip2Library::GetShuffleName(const uint8_t &shuffle) {
  return CompressionLibrary::GetDefaultShuffleName();
}

Bzip2Library::Bzip2Library() {
  number_of_modes_ = 2;
  modes_ = new std::string[number_of_modes_];
  modes_[0] = "Faster";
  modes_[1] = "Slower";
}

Bzip2Library::~Bzip2Library() { delete[] modes_; }
