/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <brotli/decode.h>
#include <brotli/encode.h>
#include <math.h>

// SMASH LIBRARIES
#include <brotli_library.hpp>
#include <options.hpp>

bool BrotliLibrary::CheckOptions(Options options) {
  bool result{true};
  result = CompressionLibrary::CheckCompressionLevel(
      "brotli", options.GetCompressionLevel(), 0, 11);
  if (result) {
    result = CompressionLibrary::CheckMode("brotli", options.GetMode(), 0, 2);
    if (result) {
      result = CompressionLibrary::CheckWindowSize(
          "brotli", options.GetWindowSize(), 10, 24);
    }
  }
  return result;
}

bool BrotliLibrary::SetOptions(Options options) {
  initialized_ = CheckOptions(options);
  if (initialized_) options_ = options;
  return initialized_;
}

void BrotliLibrary::GetCompressedDataSize(uint64_t uncompressed_size,
                                          uint64_t *compressed_size) {
  *compressed_size = BrotliEncoderMaxCompressedSize(uncompressed_size);
}

bool BrotliLibrary::Compress(char *uncompressed_data,
                             uint64_t uncompressed_size, char *compressed_data,
                             uint64_t *compressed_size) {
  bool result{initialized_};
  if (result) {
    int error = BrotliEncoderCompress(
        options_.GetCompressionLevel(), options_.GetWindowSize(),
        static_cast<BrotliEncoderMode>(options_.GetMode()), uncompressed_size,
        reinterpret_cast<uint8_t *>(uncompressed_data), compressed_size,
        reinterpret_cast<uint8_t *>(compressed_data));
    if (!error) {
      std::cout << "ERROR: brotli error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void BrotliLibrary::GetDecompressedDataSize(char *compressed_data,
                                            uint64_t compressed_size,
                                            uint64_t *decompressed_size) {
  // There is no way to obtain with Brotli
}

bool BrotliLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                               char *decompressed_data,
                               uint64_t *decompressed_size) {
  bool result{initialized_};
  if (result) {
    BrotliDecoderResult error = BrotliDecoderDecompress(
        compressed_size, reinterpret_cast<uint8_t *>(compressed_data),
        decompressed_size, reinterpret_cast<uint8_t *>(decompressed_data));
    if (BROTLI_DECODER_RESULT_SUCCESS != error) {
      std::cout << "ERROR: brotli error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void BrotliLibrary::GetTitle() {
  CompressionLibrary::GetTitle("brotli",
                               "General-puprose compression algorithm");
}

void BrotliLibrary::GetCompressionLevelInformation(
    uint8_t *minimum_level, uint8_t *maximum_level,
    std::vector<std::string> *compression_level_information) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 11;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [0-11]");
    compression_level_information->push_back("[compression]");
  }
}

void BrotliLibrary::GetWindowSizeInformation(
    uint32_t *minimum_size, uint32_t *maximum_size,
    std::vector<std::string> *window_size_information) {
  if (minimum_size) *minimum_size = 10;
  if (maximum_size) *maximum_size = 24;
  if (window_size_information) {
    window_size_information->clear();
    window_size_information->push_back("Available values [10-24]");
    window_size_information->push_back("Window size = (2^value) - 16");
    window_size_information->push_back("[compression]");
  }
}

void BrotliLibrary::GetModeInformation(
    uint8_t *minimum_mode, uint8_t *maximum_mode,
    std::vector<std::string> *mode_information) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 2;
  if (mode_information) {
    mode_information->clear();
    mode_information->push_back("Available values [0-2]");
    mode_information->push_back("0: Generic");
    mode_information->push_back("1: UTF-8 formatted text input");
    mode_information->push_back("2: Web Open Font Format input");
    mode_information->push_back("[compression]");
  }
}

void BrotliLibrary::GetWorkFactorInformation(
    uint8_t *minimum_factor, uint8_t *maximum_factor,
    std::vector<std::string> *work_factor_information) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
}

void BrotliLibrary::GetShuffleInformation(
    uint8_t *minimum_shuffle, uint8_t *maximum_shuffle,
    std::vector<std::string> *shuffle_information) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
}

void BrotliLibrary::GetNumberThreadsInformation(
    uint8_t *minimum_threads, uint8_t *maximum_threads,
    std::vector<std::string> *number_threads_information) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
}

void BrotliLibrary::GetBackReferenceBitsInformation(
    uint8_t *minimum_bits, uint8_t *maximum_bits,
    std::vector<std::string> *back_reference_information) {
  if (minimum_bits) *minimum_bits = 0;
  if (maximum_bits) *maximum_bits = 0;
  if (back_reference_information) back_reference_information->clear();
}

BrotliLibrary::BrotliLibrary() {}

BrotliLibrary::~BrotliLibrary() {}
