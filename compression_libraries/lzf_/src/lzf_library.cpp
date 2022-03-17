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

// SMASH LIBRARIES
#include <lzf_library.hpp>
#include <options.hpp>

bool LzfLibrary::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel("lzf", options, 0, 1);
  }
  return result;
}

bool LzfLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                          char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t bytes{0};
    if (options_.GetCompressionLevel() == 0) {
      bytes = lzf_compress(uncompressed_data, uncompressed_size,
                           compressed_data, *compressed_size);
    } else {
      bytes = lzf_compress_best(uncompressed_data, uncompressed_size,
                                compressed_data, *compressed_size);
    }
    if (bytes == 0) {
      std::cout << "ERROR: lzf error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_size = bytes;
    }
  }
  return result;
}

bool LzfLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                            char *decompressed_data,
                            uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t bytes = lzf_decompress(compressed_data, compressed_size,
                                    decompressed_data, *decompressed_size);
    if (bytes == 0) {
      std::cout << "ERROR: lzf error when decompress data" << std::endl;
      result = false;
    } else {
      *decompressed_size = bytes;
    }
  }
  return result;
}

void LzfLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "lzf", "Fast and easy to embed compression library");
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
