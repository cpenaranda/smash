/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <lzfse.h>

// SMASH LIBRARIES
#include <lzfse_library.hpp>
#include <options.hpp>

bool LzfseLibrary::CheckOptions(Options options) {
  bool result{true};
  return result;
}

bool LzfseLibrary::SetOptions(Options options) {
  initialized_ = CheckOptions(options);
  if (initialized_) options_ = options;
  return initialized_;
}

void LzfseLibrary::GetCompressedDataSize(uint64_t uncompressed_size,
                                         uint64_t *compressed_size) {
  // There is no way to obtain with Lzfse
  *compressed_size = ((uncompressed_size / 5000) + 1) * 5000;
}

bool LzfseLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                            char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_};
  if (result) {
    char *workmem = new char[lzfse_encode_scratch_size()];
    uint64_t final_compression_size = lzfse_encode_buffer(
        reinterpret_cast<uint8_t *>(compressed_data), *compressed_size,
        reinterpret_cast<uint8_t *>(uncompressed_data), uncompressed_size,
        workmem);
    if (final_compression_size == 0) {
      std::cout << "ERROR: lzfse error when compress data" << std::endl;
      result = false;
    }
    delete[] workmem;
    *compressed_size = final_compression_size;
  }
  return result;
}

void LzfseLibrary::GetDecompressedDataSize(char *compressed_data,
                                           uint64_t compressed_size,
                                           uint64_t *decompressed_size) {
  // There is no way to obtain with Lzfse
}

bool LzfseLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                              char *decompressed_data,
                              uint64_t *decompressed_size) {
  bool result{initialized_};
  if (result) {
    char *workmem = new char[lzfse_decode_scratch_size()];
    uint64_t final_decompression_size = lzfse_decode_buffer(
        reinterpret_cast<uint8_t *>(decompressed_data), *decompressed_size,
        reinterpret_cast<uint8_t *>(compressed_data), compressed_size, workmem);
    if (final_decompression_size != *decompressed_size) {
      std::cout << "ERROR: lzfse error when decompress data" << std::endl;
      result = false;
    }
    delete[] workmem;
  }
  return result;
}

void LzfseLibrary::GetTitle() {
  CompressionLibrary::GetTitle("lzfse",
                               "A Lempel-Ziv style data compression algorithm "
                               "using Finite State Entropy coding");
}

void LzfseLibrary::GetCompressionLevelInformation(
    uint8_t *minimum_level, uint8_t *maximum_level,
    std::vector<std::string> *compression_level_information) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 0;
  if (compression_level_information) compression_level_information->clear();
}

void LzfseLibrary::GetWindowSizeInformation(
    uint32_t *minimum_size, uint32_t *maximum_size,
    std::vector<std::string> *window_size_information) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
}

void LzfseLibrary::GetModeInformation(
    uint8_t *minimum_mode, uint8_t *maximum_mode,
    std::vector<std::string> *mode_information) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
}

void LzfseLibrary::GetWorkFactorInformation(
    uint8_t *minimum_factor, uint8_t *maximum_factor,
    std::vector<std::string> *work_factor_information) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
}

void LzfseLibrary::GetShuffleInformation(
    uint8_t *minimum_shuffle, uint8_t *maximum_shuffle,
    std::vector<std::string> *shuffle_information) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
}

void LzfseLibrary::GetNumberThreadsInformation(
    uint8_t *minimum_threads, uint8_t *maximum_threads,
    std::vector<std::string> *number_threads_information) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
}

void LzfseLibrary::GetBackReferenceBitsInformation(
    uint8_t *minimum_bits, uint8_t *maximum_bits,
    std::vector<std::string> *back_reference_information) {
  if (minimum_bits) *minimum_bits = 0;
  if (maximum_bits) *maximum_bits = 0;
  if (back_reference_information) back_reference_information->clear();
}

LzfseLibrary::LzfseLibrary() {}

LzfseLibrary::~LzfseLibrary() {}
