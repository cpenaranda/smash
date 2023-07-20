/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <bzlib.h>

// CPU-SMASH LIBRARIES
#include <bzip2_library.hpp>
#include <cpu_options.hpp>

bool Bzip2Library::CheckOptions(CpuOptions *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result =
        CpuCompressionLibrary::CheckCompressionLevel("bzip2", options, 1, 9);
    if (result) {
      result = CpuCompressionLibrary::CheckWorkFactor("bzip2", options, 0, 25);
    }
  } else {
    result = CpuCompressionLibrary::CheckMode("bzip2", options, 0, 1);
  }
  return result;
}

bool Bzip2Library::Compress(const char *const uncompressed_data,
                            const uint64_t &uncompressed_data_size,
                            char *compressed_data,
                            uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    int bzerr = BZ2_bzBuffToBuffCompress(
        compressed_data, reinterpret_cast<uint32_t *>(compressed_data_size),
        const_cast<char *const>(uncompressed_data),
        static_cast<uint32_t>(uncompressed_data_size),
        options_.GetCompressionLevel(), 0 /* verbosity */,
        options_.GetWorkFactor() * 10);
    if (bzerr != BZ_OK && bzerr != BZ_OUTBUFF_FULL) {
      std::cout << "ERROR: bzip2 error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool Bzip2Library::Decompress(const char *const compressed_data,
                              const uint64_t &compressed_data_size,
                              char *decompressed_data,
                              uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    int bzerr = BZ2_bzBuffToBuffDecompress(
        decompressed_data, reinterpret_cast<uint32_t *>(decompressed_data_size),
        const_cast<char *const>(compressed_data),
        static_cast<uint32_t>(compressed_data_size), options_.GetMode(),
        0 /* verbosity */);
    if (bzerr != BZ_OK) {
      std::cout << "ERROR: bzip2 error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void Bzip2Library::GetTitle() {
  CpuCompressionLibrary::GetTitle(
      "bzip2", "Based on Burrows-Wheeler algorithm and Huffman coding");
}

bool Bzip2Library::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 1;
  if (maximum_level) *maximum_level = 9;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [1-9]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool Bzip2Library::GetModeInformation(
    std::vector<std::string> *mode_information, uint8_t *minimum_mode,
    uint8_t *maximum_mode, const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 1;
  if (mode_information) {
    mode_information->clear();
    mode_information->push_back("Available values [0-1]");
    mode_information->push_back("0: " + modes_[0] +
                                " decompression using more memory");
    mode_information->push_back("1: " + modes_[1] +
                                " decompression using less memory");
    mode_information->push_back("[decompression]");
  }
  return true;
}

bool Bzip2Library::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 25;
  if (work_factor_information) {
    work_factor_information->clear();
    work_factor_information->push_back("Available values [0-25]");
    work_factor_information->push_back(
        "Controls the compression behaviour when there is repetitive data");
    work_factor_information->push_back("[compression]");
  }
  return true;
}

std::string Bzip2Library::GetModeName(const uint8_t &mode) {
  std::string result = "ERROR";
  if (mode < number_of_modes_) {
    result = modes_[mode];
  }
  return result;
}

Bzip2Library::Bzip2Library() {
  number_of_modes_ = 2;
  modes_ = new std::string[number_of_modes_];
  modes_[0] = "Faster";
  modes_[1] = "Slower";
}

Bzip2Library::~Bzip2Library() { delete[] modes_; }
