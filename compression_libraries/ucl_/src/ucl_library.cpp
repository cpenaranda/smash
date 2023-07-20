/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <ucl/ucl.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <ucl_library.hpp>

bool UclLibrary::CheckOptions(CpuOptions *options, const bool &compressor) {
  bool result{true};
  result = CpuCompressionLibrary::CheckMode("ucl", options, 0, 2);
  if (compressor && result) {
    result =
        CpuCompressionLibrary::CheckCompressionLevel("ucl", options, 1, 10);
  }
  return result;
}

bool UclLibrary::Compress(const char *const uncompressed_data,
                          const uint64_t &uncompressed_data_size,
                          char *compressed_data,
                          uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    int ucl_result{0};
    ucl_uint compressed_bytes = *compressed_data_size;
    switch (options_.GetMode()) {
      case 0:
        ucl_result = ucl_nrv2b_99_compress(
            reinterpret_cast<const unsigned char *const>(uncompressed_data),
            uncompressed_data_size,
            reinterpret_cast<unsigned char *>(compressed_data),
            &compressed_bytes, 0, options_.GetCompressionLevel(), nullptr,
            nullptr);
        break;
      case 1:
        ucl_result = ucl_nrv2d_99_compress(
            reinterpret_cast<const unsigned char *const>(uncompressed_data),
            uncompressed_data_size,
            reinterpret_cast<unsigned char *>(compressed_data),
            &compressed_bytes, 0, options_.GetCompressionLevel(), nullptr,
            nullptr);
        break;
      case 2:
        ucl_result = ucl_nrv2e_99_compress(
            reinterpret_cast<const unsigned char *const>(uncompressed_data),
            uncompressed_data_size,
            reinterpret_cast<unsigned char *>(compressed_data),
            &compressed_bytes, 0, options_.GetCompressionLevel(), nullptr,
            nullptr);
        break;
      default:
        break;
    }

    if (ucl_result != UCL_E_OK || compressed_bytes > *compressed_data_size) {
      std::cout << "ERROR: ucl error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_data_size = compressed_bytes;
    }
  }
  return result;
}

bool UclLibrary::Decompress(const char *const compressed_data,
                            const uint64_t &compressed_data_size,
                            char *decompressed_data,
                            uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    int ucl_result{0};
    ucl_uint decompressed_bytes = *decompressed_data_size;
    switch (options_.GetMode()) {
      case 0:
        ucl_result = ucl_nrv2b_decompress_8(
            reinterpret_cast<const unsigned char *const>(compressed_data),
            compressed_data_size,
            reinterpret_cast<unsigned char *>(decompressed_data),
            &decompressed_bytes, nullptr);
        break;
      case 1:
        ucl_result = ucl_nrv2d_decompress_8(
            reinterpret_cast<const unsigned char *const>(compressed_data),
            compressed_data_size,
            reinterpret_cast<unsigned char *>(decompressed_data),
            &decompressed_bytes, nullptr);
        break;
      case 2:
        ucl_result = ucl_nrv2e_decompress_8(
            reinterpret_cast<const unsigned char *const>(compressed_data),
            compressed_data_size,
            reinterpret_cast<unsigned char *>(decompressed_data),
            &decompressed_bytes, nullptr);
        break;
      default:
        break;
    }
    if (ucl_result != UCL_E_OK ||
        decompressed_bytes > *decompressed_data_size) {
      std::cout << "ERROR: ucl error when decompress data" << std::endl;
      result = false;
    } else {
      *decompressed_data_size = decompressed_bytes;
    }
  }
  return result;
}

void UclLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle(
      "ucl",
      "Focused on compression for generating competitive compression ratio "
      "(requires no memory for decompression)");
}

bool UclLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 1;
  if (maximum_level) *maximum_level = 10;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [1-10]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool UclLibrary::GetModeInformation(std::vector<std::string> *mode_information,
                                    uint8_t *minimum_mode,
                                    uint8_t *maximum_mode,
                                    const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 2;
  if (mode_information) {
    mode_information->clear();
    mode_information->push_back("Available values [0-2]");
    mode_information->push_back("0: " + modes_[0] + " method");
    mode_information->push_back("1: " + modes_[1] + " method");
    mode_information->push_back("2: " + modes_[2] + " method");
    mode_information->push_back("[compression/decompression]");
  }
  return true;
}

std::string UclLibrary::GetModeName(const uint8_t &mode) {
  std::string result = "ERROR";
  if (mode < number_of_modes_) {
    result = modes_[mode];
  }
  return result;
}

UclLibrary::UclLibrary() {
  number_of_modes_ = 3;
  modes_ = new std::string[number_of_modes_];
  modes_[0] = "NRV2B";
  modes_[1] = "NRV2D";
  modes_[2] = "NRV2E";
}

UclLibrary::~UclLibrary() { delete[] modes_; }
