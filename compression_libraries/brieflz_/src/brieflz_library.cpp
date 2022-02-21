/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <brieflz.h>

// SMASH LIBRARIES
#include <brieflz_library.hpp>
#include <options.hpp>

bool BrieflzLibrary::CheckOptions(const Options &options,
                                  const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel(
        "brieflz", options.GetCompressionLevel(), 1, 10);
  }
  return result;
}

bool BrieflzLibrary::SetOptionsCompressor(const Options &options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) options_ = options;
  return initialized_compressor_;
}

bool BrieflzLibrary::SetOptionsDecompressor(const Options &options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) options_ = options;
  return initialized_decompressor_;
}

void BrieflzLibrary::GetCompressedDataSize(uint64_t uncompressed_size,
                                           uint64_t *compressed_size) {
  *compressed_size = blz_max_packed_size(uncompressed_size);
}

bool BrieflzLibrary::Compress(char *uncompressed_data,
                              uint64_t uncompressed_size, char *compressed_data,
                              uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    char *workmem = new char[blz_workmem_size_level(
        uncompressed_size, options_.GetCompressionLevel())];
    uint64_t final_compression_size{0};
    final_compression_size =
        blz_pack_level(uncompressed_data, compressed_data, uncompressed_size,
                       workmem, options_.GetCompressionLevel());
    if (final_compression_size == BLZ_ERROR ||
        final_compression_size > *compressed_size) {
      std::cout << "ERROR: brieflz error when compress data" << std::endl;
      result = false;
    }
    delete[] workmem;
    *compressed_size = final_compression_size;
  }
  return result;
}

void BrieflzLibrary::GetDecompressedDataSize(char *compressed_data,
                                             uint64_t compressed_size,
                                             uint64_t *decompressed_size) {
  // There is no way to obtain with Brieflz
}

bool BrieflzLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                                char *decompressed_data,
                                uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t final_decompression_size{0};
    final_decompression_size =
        blz_depack_safe(compressed_data, compressed_size, decompressed_data,
                        *decompressed_size);
    if (final_decompression_size != *decompressed_size) {
      std::cout << "ERROR: brieflz error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void BrieflzLibrary::GetTitle() {
  CompressionLibrary::GetTitle("brieflz",
                               "Fast Lempel-Ziv compression library");
}

bool BrieflzLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 1;
  if (maximum_level) *maximum_level = 10;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [1-10]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool BrieflzLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool BrieflzLibrary::GetModeInformation(
    std::vector<std::string> *mode_information, uint8_t *minimum_mode,
    uint8_t *maximum_mode, const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
  return false;
}

bool BrieflzLibrary::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool BrieflzLibrary::GetShuffleInformation(
    std::vector<std::string> *shuffle_information, uint8_t *minimum_shuffle,
    uint8_t *maximum_shuffle) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
  return false;
}

bool BrieflzLibrary::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

std::string BrieflzLibrary::GetModeName(const uint8_t &mode) {
  return CompressionLibrary::GetDefaultModeName();
}

std::string BrieflzLibrary::GetShuffleName(const uint8_t &shuffle) {
  return CompressionLibrary::GetDefaultShuffleName();
}

BrieflzLibrary::BrieflzLibrary() {}

BrieflzLibrary::~BrieflzLibrary() {}
