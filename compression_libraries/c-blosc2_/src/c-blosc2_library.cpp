/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <blosc2.h>

// SMASH LIBRARIES
#include <c-blosc2_library.hpp>
#include <options.hpp>

bool CBlosc2Library::CheckOptions(Options options) {
  bool result{true};
  result = CompressionLibrary::CheckCompressionLevel(
      "c-blosc2", options.GetCompressionLevel(), 0, 9);
  if (result) {
    result = CompressionLibrary::CheckShuffle("c-blosc2", options.GetShuffle(),
                                              0, 2);
    if (result) {
      result = CompressionLibrary::CheckNumberThreads(
          "c-blosc2", options.GetNumberThreads(), 1, 8);
    }
  }
  return result;
}

bool CBlosc2Library::SetOptions(Options options) {
  if (initialized_) blosc_destroy();
  initialized_ = CheckOptions(options);
  if (initialized_) {
    options_ = options;
    blosc_init();
    blosc_set_compressor("blosclz");
    blosc_set_nthreads(options_.GetNumberThreads());
  }
  return initialized_;
}

void CBlosc2Library::GetCompressedDataSize(uint64_t uncompressed_size,
                                           uint64_t *compressed_size) {
  *compressed_size = uncompressed_size + BLOSC_MAX_OVERHEAD;
}

bool CBlosc2Library::Compress(char *uncompressed_data,
                              uint64_t uncompressed_size, char *compressed_data,
                              uint64_t *compressed_size) {
  bool result{initialized_};
  if (result) {
    int csize =
        blosc_compress(options_.GetCompressionLevel(), options_.GetShuffle(),
                       sizeof(char), uncompressed_size, uncompressed_data,
                       compressed_data, *compressed_size);
    if (csize == 0 || csize < 0) {
      std::cout << "ERROR: c-blosc2 error when compress data" << std::endl;
      result = false;
    }
    *compressed_size = static_cast<uint64_t>(csize);
  }
  return result;
}

void CBlosc2Library::GetDecompressedDataSize(char *compressed_data,
                                             uint64_t compressed_size,
                                             uint64_t *decompressed_size) {
  int32_t value{0};
  blosc2_cbuffer_sizes(compressed_data, nullptr, &value, nullptr);
  *decompressed_size = value;
}

bool CBlosc2Library::Decompress(char *compressed_data, uint64_t compressed_size,
                                char *decompressed_data,
                                uint64_t *decompressed_size) {
  bool result{initialized_};
  if (result) {
    int dsize = blosc_decompress(compressed_data, decompressed_data,
                                 *decompressed_size);
    if (dsize < 0) {
      std::cout << "ERROR: c-blosc2 error when decompress data" << std::endl;
      result = false;
    }
    *decompressed_size = static_cast<uint64_t>(dsize);
  }
  return result;
}

void CBlosc2Library::GetTitle() {
  CompressionLibrary::GetTitle(
      "c-blosc2", "High performance compressor optimized for binary data");
}

void CBlosc2Library::GetCompressionLevelInformation(
    uint8_t *minimum_level, uint8_t *maximum_level,
    std::vector<std::string> *compression_level_information) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 9;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [0-9]");
    compression_level_information->push_back("[compression]");
  }
}

void CBlosc2Library::GetWindowSizeInformation(
    uint32_t *minimum_size, uint32_t *maximum_size,
    std::vector<std::string> *window_size_information) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
}

void CBlosc2Library::GetModeInformation(
    uint8_t *minimum_mode, uint8_t *maximum_mode,
    std::vector<std::string> *mode_information) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
}

void CBlosc2Library::GetWorkFactorInformation(
    uint8_t *minimum_factor, uint8_t *maximum_factor,
    std::vector<std::string> *work_factor_information) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
}

void CBlosc2Library::GetShuffleInformation(
    uint8_t *minimum_shuffle, uint8_t *maximum_shuffle,
    std::vector<std::string> *shuffle_information) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 2;
  if (shuffle_information) {
    shuffle_information->clear();
    shuffle_information->push_back("Available values [0-2]");
    shuffle_information->push_back("0: No Shuffle");
    shuffle_information->push_back("1: Byte Shuffle");
    shuffle_information->push_back("2: Bit Shuffle");
    shuffle_information->push_back("[compression]");
  }
}

void CBlosc2Library::GetNumberThreadsInformation(
    uint8_t *minimum_threads, uint8_t *maximum_threads,
    std::vector<std::string> *number_threads_information) {
  if (minimum_threads) *minimum_threads = 1;
  if (maximum_threads) *maximum_threads = 8;
  if (number_threads_information) {
    number_threads_information->clear();
    number_threads_information->push_back("Available values [1-8]");
    number_threads_information->push_back("[compression/decompression]");
  }
}

void CBlosc2Library::GetBackReferenceBitsInformation(
    uint8_t *minimum_bits, uint8_t *maximum_bits,
    std::vector<std::string> *back_reference_information) {
  if (minimum_bits) *minimum_bits = 0;
  if (maximum_bits) *maximum_bits = 0;
  if (back_reference_information) back_reference_information->clear();
}

CBlosc2Library::CBlosc2Library() {}

CBlosc2Library::~CBlosc2Library() {
  if (initialized_) blosc_destroy();
}
