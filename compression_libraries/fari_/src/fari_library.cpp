/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <stddef.h>
// stddef is needed to compile correctly FastAri
#include <FastAri.h>

// SMASH LIBRARIES
#include <fari_library.hpp>
#include <options.hpp>

bool FariLibrary::CheckOptions(const Options &options, const bool &compressor) {
  bool result{true};
  return result;
}

bool FariLibrary::SetOptionsCompressor(const Options &options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) {
    options_ = options;
    if (work_mem_decompression_) {
      delete[] work_mem_decompression_;
      work_mem_decompression_ = nullptr;
    }
    if (!work_mem_compression_) {
      work_mem_compression_ = new char[FA_WORKMEM];
    }
  }
  return initialized_compressor_;
}

bool FariLibrary::SetOptionsDecompressor(const Options &options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) {
    options_ = options;
    if (work_mem_compression_) {
      delete[] work_mem_compression_;
      work_mem_compression_ = nullptr;
    }
    if (!work_mem_decompression_) {
      work_mem_decompression_ = new char[FA_WORKMEM];
    }
  }
  return initialized_decompressor_;
}

void FariLibrary::GetCompressedDataSize(char *uncompressed_data,
                                        uint64_t uncompressed_size,
                                        uint64_t *compressed_size) {
  // There is no way to obtain with Fari
  *compressed_size = ((uncompressed_size / 5000) + 1) * 5000;
}

bool FariLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                           char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    int fari_result = fa_compress(
        reinterpret_cast<unsigned char *>(uncompressed_data),
        reinterpret_cast<unsigned char *>(compressed_data),
        uncompressed_size +
            1 /*It is need because the last byte is not compressed in fari*/,
        compressed_size, work_mem_compression_);
    if (fari_result) {
      std::cout << "ERROR: fari error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool FariLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                             char *decompressed_data,
                             uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    int fari_result = fa_decompress(
        reinterpret_cast<unsigned char *>(compressed_data),
        reinterpret_cast<unsigned char *>(decompressed_data), compressed_size,
        decompressed_size, work_mem_decompression_);
    // It could return 2 because we incremente the uncompressed size by 1 to fix
    // a fari error where the last byte is not compressed
    if (fari_result != 2 && fari_result) {
      std::cout << "ERROR: fari error when decompress datas" << std::endl;
      result = false;
    }
  }
  return result;
}

void FariLibrary::GetDecompressedDataSize(char *compressed_data,
                                          uint64_t compressed_size,
                                          uint64_t *decompressed_size) {
  // There is no way to obtain with Fari
}

void FariLibrary::GetTitle() {
  CompressionLibrary::GetTitle("fari",
                               "An arithmetic compressor with extremely high "
                               "compression/decompression speeds");
}

bool FariLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 0;
  if (compression_level_information) compression_level_information->clear();
  return false;
}

bool FariLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool FariLibrary::GetModeInformation(std::vector<std::string> *mode_information,
                                     uint8_t *minimum_mode,
                                     uint8_t *maximum_mode,
                                     const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
  return false;
}

bool FariLibrary::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool FariLibrary::GetShuffleInformation(
    std::vector<std::string> *shuffle_information, uint8_t *minimum_shuffle,
    uint8_t *maximum_shuffle) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
  return false;
}

bool FariLibrary::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

std::string FariLibrary::GetModeName(const uint8_t &mode) {
  return CompressionLibrary::GetDefaultModeName();
}

std::string FariLibrary::GetShuffleName(const uint8_t &shuffle) {
  return CompressionLibrary::GetDefaultShuffleName();
}

FariLibrary::FariLibrary() {
  work_mem_compression_ = nullptr;
  work_mem_decompression_ = nullptr;
}

FariLibrary::~FariLibrary() {
  if (work_mem_compression_) delete[] work_mem_compression_;
  if (work_mem_decompression_) delete[] work_mem_decompression_;
}
