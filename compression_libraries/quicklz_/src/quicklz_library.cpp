/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <quicklz.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <quicklz_library.hpp>

bool QuicklzLibrary::CheckOptions(const Options &options,
                                  const bool &compressor) {
  bool result{true};
  return result;
}

bool QuicklzLibrary::SetOptionsCompressor(const Options &options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) options_ = options;
  return initialized_compressor_;
}

bool QuicklzLibrary::SetOptionsDecompressor(const Options &options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) options_ = options;
  return initialized_decompressor_;
}

void QuicklzLibrary::GetCompressedDataSize(char *uncompressed_data,
                                           uint64_t uncompressed_size,
                                           uint64_t *compressed_size) {
  *compressed_size = qlz_size_compressed(uncompressed_data);
}

bool QuicklzLibrary::Compress(char *uncompressed_data,
                              uint64_t uncompressed_size, char *compressed_data,
                              uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    qlz_state_compress state;
    uint64_t final_size = qlz_compress(uncompressed_data, compressed_data,
                                       uncompressed_size, &state);
    if (final_size == 0) {
      std::cout << "ERROR: quicklz error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_size = final_size;
    }
  }
  return result;
}

bool QuicklzLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                                char *decompressed_data,
                                uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    qlz_state_decompress state;
    uint64_t final_size =
        qlz_decompress(compressed_data, decompressed_data, &state);
    if (final_size == 0) {
      std::cout << "ERROR: quicklz error when decompress data" << std::endl;
      result = false;
    } else {
      *decompressed_size = final_size;
    }
  }
  return result;
}

void QuicklzLibrary::GetDecompressedDataSize(char *compressed_data,
                                             uint64_t compressed_size,
                                             uint64_t *decompressed_size) {
  *decompressed_size = qlz_size_decompressed(compressed_data);
}

void QuicklzLibrary::GetTitle() {
  CompressionLibrary::GetTitle("quicklz", "A fast GPL'd compression library.");
}

bool QuicklzLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 0;
  if (compression_level_information) compression_level_information->clear();
  return false;
}

bool QuicklzLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool QuicklzLibrary::GetModeInformation(
    std::vector<std::string> *mode_information, uint8_t *minimum_mode,
    uint8_t *maximum_mode, const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
  return false;
}

bool QuicklzLibrary::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool QuicklzLibrary::GetShuffleInformation(
    std::vector<std::string> *shuffle_information, uint8_t *minimum_shuffle,
    uint8_t *maximum_shuffle) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
  return false;
}

bool QuicklzLibrary::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

std::string QuicklzLibrary::GetModeName(const uint8_t &mode) {
  return CompressionLibrary::GetDefaultModeName();
}

std::string QuicklzLibrary::GetShuffleName(const uint8_t &shuffle) {
  return CompressionLibrary::GetDefaultShuffleName();
}

QuicklzLibrary::QuicklzLibrary() {}

QuicklzLibrary::~QuicklzLibrary() {}
