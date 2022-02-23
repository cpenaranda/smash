/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <wfLZ.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <wflz_library.hpp>

bool WflzLibrary::CheckOptions(const Options &options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel(
        "wflz", options.GetCompressionLevel(), 0, 1);
  }
  return result;
}

bool WflzLibrary::SetOptionsCompressor(const Options &options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) options_ = options;
  return initialized_compressor_;
}

bool WflzLibrary::SetOptionsDecompressor(const Options &options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) options_ = options;
  return initialized_decompressor_;
}

void WflzLibrary::GetCompressedDataSize(char *uncompressed_data,
                                        uint64_t uncompressed_size,
                                        uint64_t *compressed_size) {
  *compressed_size = wfLZ_GetMaxCompressedSize(uncompressed_size);
}

bool WflzLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                           char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint8_t *work_mememory = new uint8_t[wfLZ_GetWorkMemSize()];
    uint64_t bytes{0};
    if (options_.GetCompressionLevel() == 0) {
      bytes = wfLZ_Compress(
          reinterpret_cast<uint8_t *>(uncompressed_data), uncompressed_size,
          reinterpret_cast<uint8_t *>(compressed_data), work_mememory, 0);
    } else {
      bytes = wfLZ_CompressFast(
          reinterpret_cast<uint8_t *>(uncompressed_data), uncompressed_size,
          reinterpret_cast<uint8_t *>(compressed_data), work_mememory, 0);
    }
    if (bytes > *compressed_size) {
      std::cout << "ERROR: wflz error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_size = bytes;
    }
    delete[] work_mememory;
  }
  return result;
}

void WflzLibrary::GetDecompressedDataSize(char *compressed_data,
                                          uint64_t compressed_size,
                                          uint64_t *decompressed_size) {
  *decompressed_size =
      wfLZ_GetDecompressedSize(reinterpret_cast<uint8_t *>(compressed_data));
}

bool WflzLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                             char *decompressed_data,
                             uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t bytes{0};
    GetDecompressedDataSize(compressed_data, compressed_size, &bytes);
    if (bytes <= *decompressed_size) {
      wfLZ_Decompress(reinterpret_cast<uint8_t *>(compressed_data),
                      reinterpret_cast<uint8_t *>(decompressed_data));
      *decompressed_size = bytes;
    } else {
      std::cout << "ERROR: wflz error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void WflzLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "wflz", "A compression library designed for use in game engines");
}

bool WflzLibrary::GetCompressionLevelInformation(
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

bool WflzLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool WflzLibrary::GetModeInformation(std::vector<std::string> *mode_information,
                                     uint8_t *minimum_mode,
                                     uint8_t *maximum_mode,
                                     const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
  return false;
}

bool WflzLibrary::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool WflzLibrary::GetShuffleInformation(
    std::vector<std::string> *shuffle_information, uint8_t *minimum_shuffle,
    uint8_t *maximum_shuffle) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
  return false;
}

bool WflzLibrary::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

std::string WflzLibrary::GetModeName(const uint8_t &mode) {
  return CompressionLibrary::GetDefaultModeName();
}

std::string WflzLibrary::GetShuffleName(const uint8_t &shuffle) {
  return CompressionLibrary::GetDefaultShuffleName();
}

WflzLibrary::WflzLibrary() {}

WflzLibrary::~WflzLibrary() {}
