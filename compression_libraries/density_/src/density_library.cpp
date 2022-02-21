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

bool DensityLibrary::CheckOptions(Options options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckMode("density", options.GetMode(), 1, 3);
  }
  return result;
}

bool DensityLibrary::SetOptionsCompressor(Options options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) options_ = options;
  return initialized_compressor_;
}

bool DensityLibrary::SetOptionsDecompressor(Options options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) options_ = options;
  return initialized_decompressor_;
}

void DensityLibrary::GetCompressedDataSize(uint64_t uncompressed_size,
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

void DensityLibrary::GetDecompressedDataSize(char *compressed_data,
                                             uint64_t compressed_size,
                                             uint64_t *decompressed_size) {
  // There is no way to obtain with Density
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

bool DensityLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 0;
  if (compression_level_information) compression_level_information->clear();
  return false;
}

bool DensityLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool DensityLibrary::GetModeInformation(
    std::vector<std::string> *mode_information, uint8_t *minimum_mode,
    uint8_t *maximum_mode) {
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

bool DensityLibrary::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool DensityLibrary::GetShuffleInformation(
    std::vector<std::string> *shuffle_information, uint8_t *minimum_shuffle,
    uint8_t *maximum_shuffle) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
  return false;
}

bool DensityLibrary::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

bool DensityLibrary::GetBackReferenceBitsInformation(
    std::vector<std::string> *back_reference_information, uint8_t *minimum_bits,
    uint8_t *maximum_bits) {
  if (minimum_bits) *minimum_bits = 0;
  if (maximum_bits) *maximum_bits = 0;
  if (back_reference_information) back_reference_information->clear();
  return false;
}

std::string DensityLibrary::GetModeName(const uint8_t &mode) {
  std::string result = CompressionLibrary::GetDefaultModeName();
  if (mode < number_of_modes_) {
    result = modes_[mode];
  }
  return result;
}

std::string DensityLibrary::GetShuffleName(const uint8_t &shuffle) {
  return CompressionLibrary::GetDefaultShuffleName();
}

DensityLibrary::DensityLibrary() {
  number_of_modes_ = 3;
  modes_ = new std::string[number_of_modes_];
  modes_[0] = "Chameleon";
  modes_[1] = "Cheetah";
  modes_[2] = "Lion";
}

DensityLibrary::~DensityLibrary() { delete[] modes_; }
