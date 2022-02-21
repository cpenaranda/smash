/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <zlib.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <zlib_library.hpp>

bool ZlibLibrary::CheckOptions(Options options) {
  bool result{true};
  result = CompressionLibrary::CheckCompressionLevel(
      "zlib", options.GetCompressionLevel(), 0, 9);
  return result;
}

bool ZlibLibrary::SetOptions(Options options) {
  initialized_ = CheckOptions(options);
  if (initialized_) options_ = options;
  return initialized_;
}

void ZlibLibrary::GetCompressedDataSize(uint64_t uncompressed_size,
                                        uint64_t *compressed_size) {
  *compressed_size = compressBound(uncompressed_size);
}

bool ZlibLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                           char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_};
  if (result) {
    int err =
        compress2(reinterpret_cast<Bytef *>(compressed_data), compressed_size,
                  reinterpret_cast<Bytef *>(uncompressed_data),
                  uncompressed_size, options_.GetCompressionLevel());
    if (err != Z_OK) {
      std::cout << "ERROR: zlib error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void ZlibLibrary::GetDecompressedDataSize(char *compressed_data,
                                          uint64_t compressed_size,
                                          uint64_t *decompressed_size) {
  // There is no way to obtain with Zlib
}

bool ZlibLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                             char *decompressed_data,
                             uint64_t *decompressed_size) {
  bool result{initialized_};
  if (result) {
    int err = uncompress2(
        reinterpret_cast<Bytef *>(decompressed_data), decompressed_size,
        reinterpret_cast<Bytef *>(compressed_data), &compressed_size);
    if (err != Z_OK) {
      std::cout << "ERROR: zlib error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void ZlibLibrary::GetTitle() {
  CompressionLibrary::GetTitle("zlib",
                               "A general purpose data compression library");
}

bool ZlibLibrary::GetCompressionLevelInformation(
    uint8_t *minimum_level, uint8_t *maximum_level,
    std::vector<std::string> *compression_level_information) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 9;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [0-9]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool ZlibLibrary::GetWindowSizeInformation(
    uint32_t *minimum_size, uint32_t *maximum_size,
    std::vector<std::string> *window_size_information) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool ZlibLibrary::GetModeInformation(
    uint8_t *minimum_mode, uint8_t *maximum_mode,
    std::vector<std::string> *mode_information) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
  return false;
}

bool ZlibLibrary::GetWorkFactorInformation(
    uint8_t *minimum_factor, uint8_t *maximum_factor,
    std::vector<std::string> *work_factor_information) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool ZlibLibrary::GetShuffleInformation(
    uint8_t *minimum_shuffle, uint8_t *maximum_shuffle,
    std::vector<std::string> *shuffle_information) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
  return false;
}

bool ZlibLibrary::GetNumberThreadsInformation(
    uint8_t *minimum_threads, uint8_t *maximum_threads,
    std::vector<std::string> *number_threads_information) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

bool ZlibLibrary::GetBackReferenceBitsInformation(
    uint8_t *minimum_bits, uint8_t *maximum_bits,
    std::vector<std::string> *back_reference_information) {
  if (minimum_bits) *minimum_bits = 0;
  if (maximum_bits) *maximum_bits = 0;
  if (back_reference_information) back_reference_information->clear();
  return false;
}

std::string ZlibLibrary::GetModeName(const uint8_t &mode) {
  return CompressionLibrary::GetDefaultModeName();
}

std::string ZlibLibrary::GetShuffleName(const uint8_t &shuffle) {
  return CompressionLibrary::GetDefaultShuffleName();
}

ZlibLibrary::ZlibLibrary() {}

ZlibLibrary::~ZlibLibrary() {}
