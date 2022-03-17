/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <stddef.h>
// stddef is needed to compile correctly Lzsse
#include <lzsse2.h>
#include <lzsse4.h>
#include <lzsse8.h>

// SMASH LIBRARIES
#include <lzsse_library.hpp>
#include <options.hpp>

bool LzsseLibrary::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel("lzsse", options, 1, 17);
    if (result) {
      result = CompressionLibrary::CheckMode("lzsse", options, 0, 2);
    }
  }
  return result;
}

bool LzsseLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                            char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t compressed_bytes{0};
    switch (options_.GetMode()) {
      case 0: {
        LZSSE2_OptimalParseState *state =
            LZSSE2_MakeOptimalParseState(uncompressed_size);
        if (result = state) {
          compressed_bytes = LZSSE2_CompressOptimalParse(
              state, uncompressed_data, uncompressed_size, compressed_data,
              *compressed_size, options_.GetCompressionLevel());
          LZSSE2_FreeOptimalParseState(state);
        }
        break;
      }
      case 1: {
        LZSSE4_OptimalParseState *state =
            LZSSE4_MakeOptimalParseState(uncompressed_size);
        if (result = state) {
          compressed_bytes = LZSSE4_CompressOptimalParse(
              state, uncompressed_data, uncompressed_size, compressed_data,
              *compressed_size, options_.GetCompressionLevel());
          LZSSE4_FreeOptimalParseState(state);
        }
        break;
      }
      case 2: {
        LZSSE8_OptimalParseState *state =
            LZSSE8_MakeOptimalParseState(uncompressed_size);
        if (result = state) {
          compressed_bytes = LZSSE8_CompressOptimalParse(
              state, uncompressed_data, uncompressed_size, compressed_data,
              *compressed_size, options_.GetCompressionLevel());
          LZSSE8_FreeOptimalParseState(state);
        }
        break;
      }
      default:
        break;
    }
    if (result && compressed_bytes == 0 ||
        compressed_bytes > *compressed_size) {
      std::cout << "ERROR: lzsse error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_size = compressed_bytes;
    }
  }
  return result;
}

bool LzsseLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                              char *decompressed_data,
                              uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t decompressed_bytes{0};
    switch (options_.GetMode()) {
      case 0:
        decompressed_bytes =
            LZSSE2_Decompress(compressed_data, compressed_size,
                              decompressed_data, *decompressed_size);
        break;
      case 1:
        decompressed_bytes =
            LZSSE4_Decompress(compressed_data, compressed_size,
                              decompressed_data, *decompressed_size);
        break;
      case 2:
        decompressed_bytes =
            LZSSE8_Decompress(compressed_data, compressed_size,
                              decompressed_data, *decompressed_size);
        break;
      default:
        break;
    }
    if (decompressed_bytes == 0 || decompressed_bytes > *decompressed_size) {
      std::cout << "ERROR: lzsse error when decompress data" << std::endl;
      result = false;
    } else {
      *decompressed_size = decompressed_bytes;
    }
  }
  return result;
}

void LzsseLibrary::GetTitle() {
  CompressionLibrary::GetTitle("lzsse",
                               "LZ77-based compression library designed for a "
                               "branchless SSE decompression implementation");
}

bool LzsseLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 1;
  if (maximum_level) *maximum_level = 17;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [1-17]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool LzsseLibrary::GetModeInformation(
    std::vector<std::string> *mode_information, uint8_t *minimum_mode,
    uint8_t *maximum_mode, const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 2;
  if (mode_information) {
    mode_information->clear();
    mode_information->push_back("Available values [0-2]");
    mode_information->push_back("0: " + modes_[0] + " variant");
    mode_information->push_back("1: " + modes_[1] + " variant");
    mode_information->push_back("2: " + modes_[2] + " variant");
    mode_information->push_back("[compression/decompression]");
  }
  return true;
}

std::string LzsseLibrary::GetModeName(const uint8_t &mode) {
  std::string result = "ERROR";
  if (mode < number_of_modes_) {
    result = modes_[mode];
  }
  return result;
}

LzsseLibrary::LzsseLibrary() {
  number_of_modes_ = 3;
  modes_ = new std::string[number_of_modes_];
  modes_[0] = "LZSSE2";
  modes_[1] = "LZSSE4";
  modes_[2] = "LZSSE8";
}

LzsseLibrary::~LzsseLibrary() { delete[] modes_; }
