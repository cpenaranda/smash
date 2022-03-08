/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <pithy.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <pithy_library.hpp>

bool PithyLibrary::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel("pithy", options, 0, 9);
  }
  return result;
}

void PithyLibrary::GetCompressedDataSize(char *uncompressed_data,
                                         uint64_t uncompressed_size,
                                         uint64_t *compressed_size) {
  *compressed_size = pithy_MaxCompressedLength(uncompressed_size);
}

bool PithyLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                            char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t compressed_bytes =
        pithy_Compress(uncompressed_data, uncompressed_size, compressed_data,
                       *compressed_size, options_.GetCompressionLevel());
    if (compressed_bytes == 0 || compressed_bytes > *compressed_size) {
      std::cout << "ERROR: pithy error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_size = compressed_bytes;
    }
  }
  return result;
}

void PithyLibrary::GetDecompressedDataSize(char *compressed_data,
                                           uint64_t compressed_size,
                                           uint64_t *decompressed_size) {
  pithy_GetDecompressedLength(compressed_data, compressed_size,
                              decompressed_size);
}

bool PithyLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                              char *decompressed_data,
                              uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t decompression_bytes =
        pithy_Decompress(compressed_data, compressed_size, decompressed_data,
                         *decompressed_size);
    if (decompression_bytes < 0 && decompression_bytes > *decompressed_size) {
      std::cout << "ERROR: pithy error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void PithyLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "pithy",
      "Can be traced back to Googles snappy compression library, but has "
      "diverged quite a bit.");
}

bool PithyLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 9;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [0-9]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

PithyLibrary::PithyLibrary() {}

PithyLibrary::~PithyLibrary() {}
