/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <mscomp.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <ms_library.hpp>

bool MsLibrary::CheckOptions(CpuOptions *options, const bool &compressor) {
  bool result{true};
  result = CpuCompressionLibrary::CheckMode("ms", options, 0, 2);
  return result;
}

void MsLibrary::GetCompressedDataSize(const char *const uncompressed_data,
                                      const uint64_t &uncompressed_data_size,
                                      uint64_t *compressed_data_size) {
  *compressed_data_size =
      ms_max_compressed_size(static_cast<_MSCompFormat>(options_.GetMode() + 2),
                             uncompressed_data_size);
}

bool MsLibrary::Compress(const char *const uncompressed_data,
                         const uint64_t &uncompressed_data_size,
                         char *compressed_data,
                         uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    MSCompStatus error = ms_compress(
        static_cast<_MSCompFormat>(options_.GetMode() + 2),
        reinterpret_cast<const uint8_t *const>(uncompressed_data),
        uncompressed_data_size, reinterpret_cast<uint8_t *>(compressed_data),
        compressed_data_size);
    if (error != MSCOMP_OK) {
      std::cout << "ERROR: ms error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool MsLibrary::Decompress(const char *const compressed_data,
                           const uint64_t &compressed_data_size,
                           char *decompressed_data,
                           uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    MSCompStatus error = ms_decompress(
        static_cast<_MSCompFormat>(options_.GetMode() + 2),
        reinterpret_cast<const uint8_t *const>(compressed_data),
        compressed_data_size, reinterpret_cast<uint8_t *>(decompressed_data),
        decompressed_data_size);
    if (error != MSCOMP_OK) {
      std::cout << "ERROR: ms error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void MsLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle(
      "ms", "Open source implementations of Microsoft compression algorithms");
}

bool MsLibrary::GetModeInformation(std::vector<std::string> *mode_information,
                                   uint8_t *minimum_mode, uint8_t *maximum_mode,
                                   const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 2;
  if (mode_information) {
    mode_information->clear();
    mode_information->push_back("Available values [0-2]");
    mode_information->push_back("0: " + modes_[0]);
    mode_information->push_back("1: " + modes_[1]);
    mode_information->push_back("2: " + modes_[2]);
    mode_information->push_back("[compression/decompression]");
  }
  return true;
}

std::string MsLibrary::GetModeName(const uint8_t &mode) {
  std::string result = "ERROR";
  if (mode < number_of_modes_) {
    result = modes_[mode];
  }
  return result;
}

MsLibrary::MsLibrary() {
  number_of_modes_ = 3;
  modes_ = new std::string[number_of_modes_];
  modes_[0] = "Lznt1";
  modes_[1] = "Xpress";
  modes_[2] = "Xpress Huffman";
}

MsLibrary::~MsLibrary() { delete[] modes_; }
