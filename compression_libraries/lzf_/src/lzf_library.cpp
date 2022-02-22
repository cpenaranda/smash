/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */
extern "C" {
#include <lzf.h>

// Contains important methods without a header
#include <lzf_c_best.c>  // NOLINT
}

// SMASH LIBRARIES
#include <lzf_library.hpp>
#include <options.hpp>

bool LzfLibrary::CheckOptions(const Options &options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel(
        "lzf", options.GetCompressionLevel(), 0, 1);
  }
  return result;
}

bool LzfLibrary::SetOptionsCompressor(const Options &options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) options_ = options;
  return initialized_compressor_;
}

bool LzfLibrary::SetOptionsDecompressor(const Options &options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) options_ = options;
  return initialized_decompressor_;
}

void LzfLibrary::GetCompressedDataSize(uint64_t uncompressed_size,
                                       uint64_t *compressed_size) {
#if LZF_VERSION >= 0x0106
  *compressed_size = LZF_MAX_COMPRESSED_SIZE(uncompressed_size);
#else
  *compressed_size = ((uncompressed_size / 5000) + 1) * 5000;
#endif
}

bool LzfLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                          char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t bytes{0};
    if (options_.GetCompressionLevel() == 0) {
      bytes = lzf_compress(uncompressed_data, uncompressed_size,
                           compressed_data, *compressed_size);
    } else {
      bytes = lzf_compress_best(uncompressed_data, uncompressed_size,
                                compressed_data, *compressed_size);
    }
    if (bytes == 0) {
      std::cout << "ERROR: lzf error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_size = bytes;
    }
  }
  return result;
}

bool LzfLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                            char *decompressed_data,
                            uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t bytes = lzf_decompress(compressed_data, compressed_size,
                                    decompressed_data, *decompressed_size);
    if (bytes == 0) {
      std::cout << "ERROR: lzf error when decompress data" << std::endl;
      result = false;
    } else {
      *decompressed_size = bytes;
    }
  }
  return result;
}

void LzfLibrary::GetDecompressedDataSize(char *compressed_data,
                                         uint64_t compressed_size,
                                         uint64_t *decompressed_size) {
  // There is no way to obtain with Lzf
}

void LzfLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "lzf", "A free, fast, easy to embed compression library");
}

bool LzfLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 1;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [0-1]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool LzfLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool LzfLibrary::GetModeInformation(std::vector<std::string> *mode_information,
                                    uint8_t *minimum_mode,
                                    uint8_t *maximum_mode,
                                    const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
  return false;
}

bool LzfLibrary::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool LzfLibrary::GetShuffleInformation(
    std::vector<std::string> *shuffle_information, uint8_t *minimum_shuffle,
    uint8_t *maximum_shuffle) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
  return false;
}

bool LzfLibrary::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

std::string LzfLibrary::GetModeName(const uint8_t &mode) {
  return CompressionLibrary::GetDefaultModeName();
}

std::string LzfLibrary::GetShuffleName(const uint8_t &shuffle) {
  return CompressionLibrary::GetDefaultShuffleName();
}

LzfLibrary::LzfLibrary() {}

LzfLibrary::~LzfLibrary() {}
