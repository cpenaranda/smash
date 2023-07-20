/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <pithy.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <pithy_library.hpp>

bool PithyLibrary::CheckOptions(CpuOptions *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result =
        CpuCompressionLibrary::CheckCompressionLevel("pithy", options, 0, 9);
  }
  return result;
}

void PithyLibrary::GetCompressedDataSize(const char *const uncompressed_data,
                                         const uint64_t &uncompressed_data_size,
                                         uint64_t *compressed_data_size) {
  *compressed_data_size = pithy_MaxCompressedLength(uncompressed_data_size);
}

bool PithyLibrary::Compress(const char *const uncompressed_data,
                            const uint64_t &uncompressed_data_size,
                            char *compressed_data,
                            uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t compressed_bytes = pithy_Compress(
        uncompressed_data, uncompressed_data_size, compressed_data,
        *compressed_data_size, options_.GetCompressionLevel());
    if (compressed_bytes == 0 || compressed_bytes > *compressed_data_size) {
      std::cout << "ERROR: pithy error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_data_size = compressed_bytes;
    }
  }
  return result;
}

void PithyLibrary::GetDecompressedDataSize(const char *const compressed_data,
                                           const uint64_t &compressed_data_size,
                                           uint64_t *decompressed_data_size) {
  pithy_GetDecompressedLength(compressed_data, compressed_data_size,
                              decompressed_data_size);
}

bool PithyLibrary::Decompress(const char *const compressed_data,
                              const uint64_t &compressed_data_size,
                              char *decompressed_data,
                              uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t decompression_bytes =
        pithy_Decompress(compressed_data, compressed_data_size,
                         decompressed_data, *decompressed_data_size);
    if (decompression_bytes < 0 &&
        decompression_bytes > *decompressed_data_size) {
      std::cout << "ERROR: pithy error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void PithyLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle(
      "pithy",
      "Fast compression/decompression library originally based on Snappy");
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
