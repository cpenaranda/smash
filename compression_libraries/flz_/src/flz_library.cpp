/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <fastlz.h>

// SMASH LIBRARIES
#include <flz_library.hpp>
#include <options.hpp>

bool FlzLibrary::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel("flz", options, 1, 2);
  }
  return result;
}

bool FlzLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                          char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    int flz_result =
        fastlz_compress_level(options_.GetCompressionLevel(), uncompressed_data,
                              uncompressed_size, compressed_data);
    if (flz_result < 1) {
      std::cout << "ERROR: flz error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_size = flz_result;
    }
  }
  return result;
}

bool FlzLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                            char *decompressed_data,
                            uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    int flz_result = fastlz_decompress(compressed_data, compressed_size,
                                       decompressed_data, *decompressed_size);
    if (flz_result < 1) {
      std::cout << "ERROR: flz error when decompress data" << std::endl;
      result = false;
    } else {
      *decompressed_size = flz_result;
    }
  }
  return result;
}

void FlzLibrary::GetTitle() {
  CompressionLibrary::GetTitle("flz",
                               "Lightning-fast lossless compression library");
}

bool FlzLibrary::GetCompressionLevelInformation(
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

FlzLibrary::FlzLibrary() {}

FlzLibrary::~FlzLibrary() {}
