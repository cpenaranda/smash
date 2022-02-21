/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <zstd.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <zstd_library.hpp>

bool ZstdLibrary::CheckOptions(Options options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel(
        "zstd", options.GetCompressionLevel(), 1, 22);
  }
  return result;
}

bool ZstdLibrary::SetOptionsCompressor(Options options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) options_ = options;
  return initialized_compressor_;
}

bool ZstdLibrary::SetOptionsDecompressor(Options options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) options_ = options;
  return initialized_decompressor_;
}

void ZstdLibrary::GetCompressedDataSize(uint64_t uncompressed_size,
                                        uint64_t *compressed_size) {
  *compressed_size = ZSTD_compressBound(uncompressed_size);
}

bool ZstdLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                           char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t new_size =
        ZSTD_compress(compressed_data, *compressed_size, uncompressed_data,
                      uncompressed_size, options_.GetCompressionLevel());
    if (new_size > *compressed_size) {
      std::cout << "ERROR: zstd error when compress data" << std::endl;
      result = false;
    }
    *compressed_size = new_size;
  }
  return result;
}

void ZstdLibrary::GetDecompressedDataSize(char *compressed_data,
                                          uint64_t compressed_size,
                                          uint64_t *decompressed_size) {
  // There is no way to obtain with ZSTD
}

bool ZstdLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                             char *decompressed_data,
                             uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t new_size = ZSTD_decompress(decompressed_data, *decompressed_size,
                                        compressed_data, compressed_size);
    if (new_size != *decompressed_size) {
      std::cout << "ERROR: zstd error when decompress data" << std::endl;
      result = false;
    }
    *decompressed_size = new_size;
  }
  return result;
}

void ZstdLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "zstd",
      "A fast lossless compression algorithm, targeting real-time compression "
      "scenarios at zlib-level and better compression ratios");
}

bool ZstdLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 1;
  if (maximum_level) *maximum_level = 22;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [1-22]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool ZstdLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool ZstdLibrary::GetModeInformation(std::vector<std::string> *mode_information,
                                     uint8_t *minimum_mode,
                                     uint8_t *maximum_mode,
                                     const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
  return false;
}

bool ZstdLibrary::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool ZstdLibrary::GetShuffleInformation(
    std::vector<std::string> *shuffle_information, uint8_t *minimum_shuffle,
    uint8_t *maximum_shuffle) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
  return false;
}

bool ZstdLibrary::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

std::string ZstdLibrary::GetModeName(const uint8_t &mode) {
  return CompressionLibrary::GetDefaultModeName();
}

std::string ZstdLibrary::GetShuffleName(const uint8_t &shuffle) {
  return CompressionLibrary::GetDefaultShuffleName();
}

ZstdLibrary::ZstdLibrary() {}

ZstdLibrary::~ZstdLibrary() {}
