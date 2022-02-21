/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <mscomp.h>

// SMASH LIBRARIES
#include <ms_library.hpp>
#include <options.hpp>

bool MsLibrary::CheckOptions(Options options, const bool &compressor) {
  bool result{true};
  result = CompressionLibrary::CheckMode("ms", options.GetMode(), 0, 2);
  return result;
}

bool MsLibrary::SetOptionsCompressor(Options options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) options_ = options;
  return initialized_compressor_;
}

bool MsLibrary::SetOptionsDecompressor(Options options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) options_ = options;
  return initialized_decompressor_;
}

void MsLibrary::GetCompressedDataSize(uint64_t uncompressed_size,
                                      uint64_t *compressed_size) {
  *compressed_size = ms_max_compressed_size(
      static_cast<_MSCompFormat>(options_.GetMode() + 2), uncompressed_size);
}

bool MsLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                         char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    MSCompStatus error = ms_compress(
        static_cast<_MSCompFormat>(options_.GetMode() + 2),
        reinterpret_cast<bytes>(uncompressed_data), uncompressed_size,
        reinterpret_cast<bytes>(compressed_data), compressed_size);
    if (error != MSCOMP_OK) {
      std::cout << "ERROR: ms error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void MsLibrary::GetDecompressedDataSize(char *compressed_data,
                                        uint64_t compressed_size,
                                        uint64_t *decompressed_size) {
  // There is no way to obtain with Ms
}

bool MsLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                           char *decompressed_data,
                           uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    MSCompStatus error = ms_decompress(
        static_cast<_MSCompFormat>(options_.GetMode() + 2),
        reinterpret_cast<bytes>(compressed_data), compressed_size,
        reinterpret_cast<bytes>(decompressed_data), decompressed_size);
    if (error != MSCOMP_OK) {
      std::cout << "ERROR: ms error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void MsLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "ms", "Open source implementations of Microsoft compression algorithms");
}

bool MsLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 0;
  if (compression_level_information) compression_level_information->clear();
  return false;
}

bool MsLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool MsLibrary::GetModeInformation(std::vector<std::string> *mode_information,
                                   uint8_t *minimum_mode, uint8_t *maximum_mode,
                                   const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 2;
  if (mode_information) {
    mode_information->clear();
    mode_information->push_back("Available values [0-2]");
    mode_information->push_back("0: " + modes_[0]);
    mode_information->push_back("1: " + modes_[1]);
    mode_information->push_back("2: " + modes_[2]);
    mode_information->push_back("[compression/decompression]");
  }
  return true;
}

bool MsLibrary::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool MsLibrary::GetShuffleInformation(
    std::vector<std::string> *shuffle_information, uint8_t *minimum_shuffle,
    uint8_t *maximum_shuffle) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
  return false;
}

bool MsLibrary::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

std::string MsLibrary::GetModeName(const uint8_t &mode) {
  std::string result = CompressionLibrary::GetDefaultModeName();
  if (mode < number_of_modes_) {
    result = modes_[mode];
  }
  return result;
}

std::string MsLibrary::GetShuffleName(const uint8_t &shuffle) {
  return CompressionLibrary::GetDefaultShuffleName();
}

MsLibrary::MsLibrary() {
  number_of_modes_ = 3;
  modes_ = new std::string[number_of_modes_];
  modes_[0] = "Lznt1";
  modes_[1] = "Xpress";
  modes_[2] = "Xpress Huffman";
}

MsLibrary::~MsLibrary() { delete[] modes_; }
