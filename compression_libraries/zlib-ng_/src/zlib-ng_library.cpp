/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <zlib-ng.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <zlib-ng_library.hpp>

bool ZlibNgLibrary::CheckOptions(Options options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel(
        "zlib-ng", options.GetCompressionLevel(), 0, 9);
  }
  return result;
}

bool ZlibNgLibrary::SetOptionsCompressor(Options options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) options_ = options;
  return initialized_compressor_;
}

bool ZlibNgLibrary::SetOptionsDecompressor(Options options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) options_ = options;
  return initialized_decompressor_;
}

void ZlibNgLibrary::GetCompressedDataSize(uint64_t uncompressed_size,
                                          uint64_t *compressed_size) {
  *compressed_size = zng_compressBound(uncompressed_size);
}

bool ZlibNgLibrary::Compress(char *uncompressed_data,
                             uint64_t uncompressed_size, char *compressed_data,
                             uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    int err = zng_compress2(reinterpret_cast<Bytef *>(compressed_data),
                            compressed_size,
                            reinterpret_cast<Bytef *>(uncompressed_data),
                            uncompressed_size, options_.GetCompressionLevel());
    if (err != Z_OK) {
      std::cout << "ERROR: zlib-ng error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void ZlibNgLibrary::GetDecompressedDataSize(char *compressed_data,
                                            uint64_t compressed_size,
                                            uint64_t *decompressed_size) {
  // There is no way to obtain with Zlib-ng
}

bool ZlibNgLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                               char *decompressed_data,
                               uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    int err = zng_uncompress2(
        reinterpret_cast<Bytef *>(decompressed_data), decompressed_size,
        reinterpret_cast<Bytef *>(compressed_data), &compressed_size);
    if (err != Z_OK) {
      std::cout << "ERROR: zlib-ng error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void ZlibNgLibrary::GetTitle() {
  CompressionLibrary::GetTitle("zlib-ng",
                               "zlib for the next generation systems");
}

bool ZlibNgLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 9;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [0-9]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool ZlibNgLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool ZlibNgLibrary::GetModeInformation(
    std::vector<std::string> *mode_information, uint8_t *minimum_mode,
    uint8_t *maximum_mode, const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
  return false;
}

bool ZlibNgLibrary::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool ZlibNgLibrary::GetShuffleInformation(
    std::vector<std::string> *shuffle_information, uint8_t *minimum_shuffle,
    uint8_t *maximum_shuffle) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
  return false;
}

bool ZlibNgLibrary::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

std::string ZlibNgLibrary::GetModeName(const uint8_t &mode) {
  return CompressionLibrary::GetDefaultModeName();
}

std::string ZlibNgLibrary::GetShuffleName(const uint8_t &shuffle) {
  return CompressionLibrary::GetDefaultShuffleName();
}

ZlibNgLibrary::ZlibNgLibrary() {}

ZlibNgLibrary::~ZlibNgLibrary() {}
