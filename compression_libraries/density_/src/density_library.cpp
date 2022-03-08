/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <density_api.h>

// SMASH LIBRARIES
#include <density_library.hpp>
#include <options.hpp>

bool DensityLibrary::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckMode("density", options, 1, 3);
  }
  return result;
}

void DensityLibrary::GetCompressedDataSize(char *uncompressed_data,
                                           uint64_t uncompressed_size,
                                           uint64_t *compressed_size) {
  *compressed_size = density_compress_safe_size(uncompressed_size);
}

bool DensityLibrary::Compress(char *uncompressed_data,
                              uint64_t uncompressed_size, char *compressed_data,
                              uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    density_processing_result res = density_compress(
        reinterpret_cast<uint8_t *>(uncompressed_data), uncompressed_size,
        reinterpret_cast<uint8_t *>(compressed_data), *compressed_size,
        static_cast<DENSITY_ALGORITHM>(options_.GetMode()));
    if (res.state || res.bytesWritten > *compressed_size) {
      std::cout << "ERROR: density error when compress data" << std::endl;
      result = false;
    }
    *compressed_size = res.bytesWritten;
  }
  return result;
}

bool DensityLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                                char *decompressed_data,
                                uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    density_processing_result res = density_decompress(
        reinterpret_cast<uint8_t *>(compressed_data), compressed_size,
        reinterpret_cast<uint8_t *>(decompressed_data),
        density_decompress_safe_size(*decompressed_size));
    if (res.state || res.bytesWritten != *decompressed_size) {
      std::cout << "ERROR: density error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void DensityLibrary::GetTitle() {
  CompressionLibrary::GetTitle("density", "Superfast compression library");
}

bool DensityLibrary::GetModeInformation(
    std::vector<std::string> *mode_information, uint8_t *minimum_mode,
    uint8_t *maximum_mode, const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 1;
  if (maximum_mode) *maximum_mode = 3;
  if (mode_information) {
    mode_information->clear();
    mode_information->push_back("Available values [1-3]");
    mode_information->push_back("1: " + modes_[0] + " algorithm");
    mode_information->push_back("2: " + modes_[1] + " algorithm");
    mode_information->push_back("3: " + modes_[2] + " algorithm");
    mode_information->push_back("[compression]");
  }
  return true;
}

std::string DensityLibrary::GetModeName(const uint8_t &mode) {
  std::string result = "ERROR";
  if (mode - 1 < number_of_modes_) {
    result = modes_[mode - 1];
  }
  return result;
}

DensityLibrary::DensityLibrary() {
  number_of_modes_ = 3;
  modes_ = new std::string[number_of_modes_];
  modes_[0] = "Chameleon";
  modes_[1] = "Cheetah";
  modes_[2] = "Lion";
}

DensityLibrary::~DensityLibrary() { delete[] modes_; }
