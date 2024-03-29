/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <lodepng.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <lodepng_library.hpp>

bool LodepngLibrary::CheckOptions(CpuOptions *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result =
        CpuCompressionLibrary::CheckCompressionLevel("lodepng", options, 1, 2);
    if (result) {
      result =
          CpuCompressionLibrary::CheckWindowSize("lodepng", options, 10, 15);
      if (result) {
        result =
            CpuCompressionLibrary::CheckWorkFactor("lodepng", options, 1, 20);
        if (result) {
          result = CpuCompressionLibrary::CheckFlags("lodepng", options, 0, 1);
          if (result) {
            result = CpuCompressionLibrary::CheckBackReference("lodepng",
                                                               options, 1, 8);
          }
        }
      }
    }
  }
  return result;
}

bool LodepngLibrary::Compress(const char *const uncompressed_data,
                              const uint64_t &uncompressed_data_size,
                              char *compressed_data,
                              uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    LodePNGCompressSettings settings = {
        options_.GetCompressionLevel(),
        1,
        static_cast<unsigned>(1 << options_.GetWindowSize()),
        options_.GetWorkFactor(),
        static_cast<unsigned int>((1 << options_.GetBackReference()) - 1),
        options_.GetFlags(),
        0,
        0,
        0};

    unsigned char *data{nullptr};
    uint64_t data_size = 0;
    unsigned int lodepng_result = lodepng_zlib_compress(
        &data, &data_size,
        reinterpret_cast<const unsigned char *const>(uncompressed_data),
        uncompressed_data_size, &settings);
    if (lodepng_result != 0 || data_size > *compressed_data_size) {
      std::cout << "ERROR: lodepng error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_data_size = data_size;
      memcpy(compressed_data, data, data_size);
      free(data);
    }
  }
  return result;
}

bool LodepngLibrary::Decompress(const char *const compressed_data,
                                const uint64_t &compressed_data_size,
                                char *decompressed_data,
                                uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    LodePNGDecompressSettings settings = {0, 0, 0, 0, 0, 0};
    unsigned char *data{nullptr};
    uint64_t data_size = 0;
    unsigned int lodepng_result = lodepng_zlib_decompress(
        &data, &data_size,
        reinterpret_cast<const unsigned char *const>(compressed_data),
        compressed_data_size, &settings);
    if (lodepng_result != 0 || data_size > *decompressed_data_size) {
      std::cout << "ERROR: lodepng error when decompress data" << std::endl;
      result = false;
    } else {
      *decompressed_data_size = data_size;
      memcpy(decompressed_data, data, data_size);
      free(data);
    }
  }
  return result;
}

void LodepngLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle(
      "lodepng", "PNG encoder and decoder in C and C++, without dependencies");
}

bool LodepngLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 1;
  if (maximum_level) *maximum_level = 2;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [1-2]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool LodepngLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 10;
  if (maximum_size) *maximum_size = 15;
  if (window_size_information) {
    window_size_information->clear();
    window_size_information->push_back("Available values [10-15]");
    window_size_information->push_back("[compression]");
  }
  return true;
}

bool LodepngLibrary::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 1;
  if (maximum_factor) *maximum_factor = 20;
  if (work_factor_information) {
    work_factor_information->clear();
    work_factor_information->push_back("Available values [1-20]");
    work_factor_information->push_back("[compression]");
  }
  return true;
}

bool LodepngLibrary::GetFlagsInformation(
    std::vector<std::string> *flags_information, uint8_t *minimum_flags,
    uint8_t *maximum_flags) {
  if (minimum_flags) *minimum_flags = 0;
  if (maximum_flags) *maximum_flags = 1;
  if (flags_information) {
    flags_information->clear();
    flags_information->push_back("Available values [0-1]");
    flags_information->push_back("0: " + flags_[0] + " compression");
    flags_information->push_back("1: " + flags_[1] + " compression");
    flags_information->push_back("[compression]");
  }
  return true;
}

bool LodepngLibrary::GetBackReferenceInformation(
    std::vector<std::string> *back_reference_information,
    uint8_t *minimum_back_reference, uint8_t *maximum_back_reference) {
  if (minimum_back_reference) *minimum_back_reference = 1;
  if (maximum_back_reference) *maximum_back_reference = 8;
  if (back_reference_information) {
    back_reference_information->clear();
    back_reference_information->push_back("Available values [1-8]");
    back_reference_information->push_back("[compression]");
  }
  return true;
}

std::string LodepngLibrary::GetFlagsName(const uint8_t &flags) {
  std::string result = "ERROR";
  if (flags < number_of_flags_) {
    result = flags_[flags];
  }
  return result;
}

LodepngLibrary::LodepngLibrary() {
  number_of_flags_ = 2;
  flags_ = new std::string[number_of_flags_];
  flags_[0] = "Fast";
  flags_[1] = "Slow";
}

LodepngLibrary::~LodepngLibrary() { delete[] flags_; }
