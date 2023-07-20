/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <snappy-c.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <snappy_library.hpp>

void SnappyLibrary::GetCompressedDataSize(
    const char *const uncompressed_data, const uint64_t &uncompressed_data_size,
    uint64_t *compressed_data_size) {
  *compressed_data_size = snappy_max_compressed_length(uncompressed_data_size);
}

bool SnappyLibrary::Compress(const char *const uncompressed_data,
                             const uint64_t &uncompressed_data_size,
                             char *compressed_data,
                             uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    snappy_status error =
        snappy_compress(uncompressed_data, uncompressed_data_size,
                        compressed_data, compressed_data_size);
    if (SNAPPY_OK != error) {
      std::cout << "ERROR: snappy error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void SnappyLibrary::GetDecompressedDataSize(
    const char *const compressed_data, const uint64_t &compressed_data_size,
    uint64_t *decompressed_data_size) {
  snappy_uncompressed_length(compressed_data, compressed_data_size,
                             decompressed_data_size);
}

bool SnappyLibrary::Decompress(const char *const compressed_data,
                               const uint64_t &compressed_data_size,
                               char *decompressed_data,
                               uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    snappy_status error =
        snappy_uncompress(compressed_data, compressed_data_size,
                          decompressed_data, decompressed_data_size);
    if (SNAPPY_OK != error) {
      std::cout << "ERROR: snappy error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void SnappyLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle(
      "snappy", "Fast compressor/decompressor created by Google");
}

SnappyLibrary::SnappyLibrary() {}

SnappyLibrary::~SnappyLibrary() {}
