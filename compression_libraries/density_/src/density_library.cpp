/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <density_api.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <density_library.hpp>

bool DensityLibrary::CheckOptions(CpuOptions *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CpuCompressionLibrary::CheckMode("density", options, 1, 3);
  }
  return result;
}

void DensityLibrary::GetCompressedDataSize(
    const char *const uncompressed_data, const uint64_t &uncompressed_data_size,
    uint64_t *compressed_data_size) {
  *compressed_data_size = density_compress_safe_size(uncompressed_data_size);
}

bool DensityLibrary::Compress(const char *const uncompressed_data,
                              const uint64_t &uncompressed_data_size,
                              char *compressed_data,
                              uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    density_processing_result res = density_compress(
        reinterpret_cast<const uint8_t *const>(uncompressed_data),
        uncompressed_data_size, reinterpret_cast<uint8_t *>(compressed_data),
        *compressed_data_size,
        static_cast<DENSITY_ALGORITHM>(options_.GetMode()));
    if (res.state || res.bytesWritten > *compressed_data_size) {
      std::cout << "ERROR: density error when compress data" << std::endl;
      result = false;
    }
    *compressed_data_size = res.bytesWritten;
  }
  return result;
}

bool DensityLibrary::Decompress(const char *const compressed_data,
                                const uint64_t &compressed_data_size,
                                char *decompressed_data,
                                uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    density_processing_result res = density_decompress(
        reinterpret_cast<const uint8_t *const>(compressed_data),
        compressed_data_size, reinterpret_cast<uint8_t *>(decompressed_data),
        *decompressed_data_size);
    if (res.state || res.bytesWritten != *decompressed_data_size) {
      std::cout << "ERROR: density error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void DensityLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle(
      "density",
      "Focused on high-speed compression, at the best ratio possible");
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
