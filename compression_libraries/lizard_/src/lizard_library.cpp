/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <lizard_compress.h>
#include <lizard_decompress.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <lizard_library.hpp>

bool LizardLibrary::CheckOptions(CpuOptions *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result =
        CpuCompressionLibrary::CheckCompressionLevel("lizard", options, 0, 9);
    if (result) {
      result = CpuCompressionLibrary::CheckMode("lizard", options, 0, 3);
    }
  }
  return result;
}

void LizardLibrary::GetCompressedDataSize(
    const char *const uncompressed_data, const uint64_t &uncompressed_data_size,
    uint64_t *compressed_data_size) {
  *compressed_data_size = Lizard_compressBound(uncompressed_data_size);
}

bool LizardLibrary::Compress(const char *const uncompressed_data,
                             const uint64_t &uncompressed_data_size,
                             char *compressed_data,
                             uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t compressed_bytes = Lizard_compress(
        uncompressed_data, compressed_data, uncompressed_data_size,
        *compressed_data_size,
        options_.GetCompressionLevel() + ((options_.GetMode() + 1) * 10));
    if (compressed_bytes == 0 || compressed_bytes > *compressed_data_size) {
      std::cout << "ERROR: lizard error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_data_size = compressed_bytes;
    }
  }
  return result;
}

bool LizardLibrary::Decompress(const char *const compressed_data,
                               const uint64_t &compressed_data_size,
                               char *decompressed_data,
                               uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t decompressed_bytes =
        Lizard_decompress_safe(compressed_data, decompressed_data,
                               compressed_data_size, *decompressed_data_size);
    if (decompressed_bytes == 0 ||
        decompressed_bytes > *decompressed_data_size) {
      std::cout << "ERROR: lizard error when decompress data" << std::endl;
      result = false;
    } else {
      *decompressed_data_size = decompressed_bytes;
    }
  }
  return result;
}

void LizardLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle(
      "lizard",
      "Lossless compression algorithm which contains 4 compression modes");
}

bool LizardLibrary::GetCompressionLevelInformation(
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

bool LizardLibrary::GetModeInformation(
    std::vector<std::string> *mode_information, uint8_t *minimum_mode,
    uint8_t *maximum_mode, const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 3;
  if (mode_information) {
    mode_information->clear();
    mode_information->push_back("Available values [0-3]");
    mode_information->push_back("0: " + modes_[0] + " method");
    mode_information->push_back("1: " + modes_[1] + " method");
    mode_information->push_back("2: " + modes_[2] + " method");
    mode_information->push_back("3: " + modes_[3] + " method");
    mode_information->push_back("[compression]");
  }
  return true;
}

std::string LizardLibrary::GetModeName(const uint8_t &mode) {
  std::string result = "ERROR";
  if (mode < number_of_modes_) {
    result = modes_[mode];
  }
  return result;
}

LizardLibrary::LizardLibrary() {
  number_of_modes_ = 4;
  modes_ = new std::string[number_of_modes_];
  modes_[0] = "FastLZ4";
  modes_[1] = "LIZv1";
  modes_[2] = "FastLZ4 + Huff";
  modes_[3] = "LIZv1 + Huff";
}

LizardLibrary::~LizardLibrary() { delete[] modes_; }
