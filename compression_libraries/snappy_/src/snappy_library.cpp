/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <snappy-c.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <snappy_library.hpp>

bool SnappyLibrary::CheckOptions(Options options) {
  bool result{true};
  return result;
}

bool SnappyLibrary::SetOptions(Options options) {
  initialized_ = CheckOptions(options);
  if (initialized_) options_ = options;
  return initialized_;
}

void SnappyLibrary::GetCompressedDataSize(uint64_t uncompressed_size,
                                          uint64_t *compressed_size) {
  *compressed_size = snappy_max_compressed_length(uncompressed_size);
}

bool SnappyLibrary::Compress(char *uncompressed_data,
                             uint64_t uncompressed_size, char *compressed_data,
                             uint64_t *compressed_size) {
  bool result{initialized_};
  if (result) {
    snappy_status error = snappy_compress(uncompressed_data, uncompressed_size,
                                          compressed_data, compressed_size);
    if (SNAPPY_OK != error) {
      std::cout << "ERROR: snappy error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void SnappyLibrary::GetDecompressedDataSize(char *compressed_data,
                                            uint64_t compressed_size,
                                            uint64_t *decompressed_size) {
  snappy_uncompressed_length(compressed_data, compressed_size,
                             decompressed_size);
}

bool SnappyLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                               char *decompressed_data,
                               uint64_t *decompressed_size) {
  bool result{initialized_};
  if (result) {
    snappy_status error = snappy_uncompress(
        compressed_data, compressed_size, decompressed_data, decompressed_size);
    if (SNAPPY_OK != error) {
      std::cout << "ERROR: snappy error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void SnappyLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "snappy", "A fast compressor/decompressor created by Google");
}

bool SnappyLibrary::GetCompressionLevelInformation(
    uint8_t *minimum_level, uint8_t *maximum_level,
    std::vector<std::string> *compression_level_information) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 0;
  if (compression_level_information) compression_level_information->clear();
  return false;
}

bool SnappyLibrary::GetWindowSizeInformation(
    uint32_t *minimum_size, uint32_t *maximum_size,
    std::vector<std::string> *window_size_information) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool SnappyLibrary::GetModeInformation(
    uint8_t *minimum_mode, uint8_t *maximum_mode,
    std::vector<std::string> *mode_information) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
  return false;
}

bool SnappyLibrary::GetWorkFactorInformation(
    uint8_t *minimum_factor, uint8_t *maximum_factor,
    std::vector<std::string> *work_factor_information) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool SnappyLibrary::GetShuffleInformation(
    uint8_t *minimum_shuffle, uint8_t *maximum_shuffle,
    std::vector<std::string> *shuffle_information) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
  return false;
}

bool SnappyLibrary::GetNumberThreadsInformation(
    uint8_t *minimum_threads, uint8_t *maximum_threads,
    std::vector<std::string> *number_threads_information) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

bool SnappyLibrary::GetBackReferenceBitsInformation(
    uint8_t *minimum_bits, uint8_t *maximum_bits,
    std::vector<std::string> *back_reference_information) {
  if (minimum_bits) *minimum_bits = 0;
  if (maximum_bits) *maximum_bits = 0;
  if (back_reference_information) back_reference_information->clear();
  return false;
}

std::string SnappyLibrary::GetModeName(const uint8_t &mode) {
  return CompressionLibrary::GetDefaultModeName();
}

std::string SnappyLibrary::GetShuffleName(const uint8_t &shuffle) {
  return CompressionLibrary::GetDefaultShuffleName();
}

SnappyLibrary::SnappyLibrary() {}

SnappyLibrary::~SnappyLibrary() {}
