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

bool ZstdLibrary::CheckOptions(Options options) {
  bool result{true};
  result = CompressionLibrary::CheckCompressionLevel(
      "zstd", options.GetCompressionLevel(), 1, 22);
  return result;
}

bool ZstdLibrary::SetOptions(Options options) {
  initialized_ = CheckOptions(options);
  if (initialized_) options_ = options;
  return initialized_;
}

void ZstdLibrary::GetCompressedDataSize(uint64_t uncompressed_size,
                                        uint64_t *compressed_size) {
  *compressed_size = ZSTD_compressBound(uncompressed_size);
}

bool ZstdLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                           char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_};
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
  bool result{initialized_};
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
    uint8_t *minimum_level, uint8_t *maximum_level,
    std::vector<std::string> *compression_level_information) {
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
    uint32_t *minimum_size, uint32_t *maximum_size,
    std::vector<std::string> *window_size_information) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool ZstdLibrary::GetModeInformation(
    uint8_t *minimum_mode, uint8_t *maximum_mode,
    std::vector<std::string> *mode_information) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
  return false;
}

bool ZstdLibrary::GetWorkFactorInformation(
    uint8_t *minimum_factor, uint8_t *maximum_factor,
    std::vector<std::string> *work_factor_information) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool ZstdLibrary::GetShuffleInformation(
    uint8_t *minimum_shuffle, uint8_t *maximum_shuffle,
    std::vector<std::string> *shuffle_information) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
  return false;
}

bool ZstdLibrary::GetNumberThreadsInformation(
    uint8_t *minimum_threads, uint8_t *maximum_threads,
    std::vector<std::string> *number_threads_information) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

bool ZstdLibrary::GetBackReferenceBitsInformation(
    uint8_t *minimum_bits, uint8_t *maximum_bits,
    std::vector<std::string> *back_reference_information) {
  if (minimum_bits) *minimum_bits = 0;
  if (maximum_bits) *maximum_bits = 0;
  if (back_reference_information) back_reference_information->clear();
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
