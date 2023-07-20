/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */
extern "C" {
#include <lzf.h>

// Contains important methods without a header
#include <lzf_c_best.c>  // NOLINT
}

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <lzf_library.hpp>

bool LzfLibrary::CheckOptions(CpuOptions *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CpuCompressionLibrary::CheckCompressionLevel("lzf", options, 0, 1);
  }
  return result;
}

bool LzfLibrary::Compress(const char *const uncompressed_data,
                          const uint64_t &uncompressed_data_size,
                          char *compressed_data,
                          uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t bytes{0};
    if (options_.GetCompressionLevel() == 0) {
      bytes = lzf_compress(uncompressed_data, uncompressed_data_size,
                           compressed_data, *compressed_data_size);
    } else {
      bytes = lzf_compress_best(uncompressed_data, uncompressed_data_size,
                                compressed_data, *compressed_data_size);
    }
    if (bytes == 0) {
      std::cout << "ERROR: lzf error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_data_size = bytes;
    }
  }
  return result;
}

bool LzfLibrary::Decompress(const char *const compressed_data,
                            const uint64_t &compressed_data_size,
                            char *decompressed_data,
                            uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t bytes = lzf_decompress(compressed_data, compressed_data_size,
                                    decompressed_data, *decompressed_data_size);
    if (bytes == 0) {
      std::cout << "ERROR: lzf error when decompress data" << std::endl;
      result = false;
    } else {
      *decompressed_data_size = bytes;
    }
  }
  return result;
}

void LzfLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle("lzf",
                                  "Fast and easy to embed compression library");
}

bool LzfLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 1;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [0-1]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

LzfLibrary::LzfLibrary() {}

LzfLibrary::~LzfLibrary() {}
