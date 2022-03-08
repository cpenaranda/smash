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

bool BrotliLibrary::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result =
        CompressionLibrary::CheckCompressionLevel("brotli", options, 0, 11);
    if (result) {
      result = CompressionLibrary::CheckMode("brotli", options, 0, 2);
      if (result) {
        result = CompressionLibrary::CheckWindowSize("brotli", options, 10, 24);
      }
    }
  }
  return result;
}

void BrotliLibrary::GetCompressedDataSize(char *uncompressed_data,
                                          uint64_t uncompressed_size,
                                          uint64_t *compressed_size) {
  *compressed_size = BrotliEncoderMaxCompressedSize(uncompressed_size);
}

bool BrotliLibrary::Compress(char *uncompressed_data,
                             uint64_t uncompressed_size, char *compressed_data,
                             uint64_t *compressed_size) {
  bool result{initialized_compressor_};
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

bool BrotliLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                               char *decompressed_data,
                               uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
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

bool BrotliLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 11;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [0-11]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool BrotliLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 10;
  if (maximum_size) *maximum_size = 24;
  if (window_size_information) {
    window_size_information->clear();
    window_size_information->push_back("Available values [10-24]");
    window_size_information->push_back("Window size = (2^value) - 16");
    window_size_information->push_back("[compression]");
  }
  return true;
}

bool BrotliLibrary::GetModeInformation(
    std::vector<std::string> *mode_information, uint8_t *minimum_mode,
    uint8_t *maximum_mode, const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 2;
  if (mode_information) {
    mode_information->clear();
    mode_information->push_back("Available values [0-2]");
    mode_information->push_back("0: " + modes_[0]);
    mode_information->push_back("1: " + modes_[1] + " input");
    mode_information->push_back("2: " + modes_[2] + " input");
    mode_information->push_back("[compression]");
  }
  return true;
}

std::string BrotliLibrary::GetModeName(const uint8_t &mode) {
  std::string result = "ERROR";
  if (mode < number_of_modes_) {
    result = modes_[mode];
  }
  return result;
}

BrotliLibrary::BrotliLibrary() {
  number_of_modes_ = 3;
  modes_ = new std::string[number_of_modes_];
  modes_[0] = "Generic";
  modes_[1] = "UTF-8";
  modes_[2] = "WOFF";
}

BrotliLibrary::~BrotliLibrary() { delete[] modes_; }
