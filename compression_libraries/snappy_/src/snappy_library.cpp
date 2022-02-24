/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <snappy-c.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <snappy_library.hpp>

void SnappyLibrary::GetCompressedDataSize(char *uncompressed_data,
                                          uint64_t uncompressed_size,
                                          uint64_t *compressed_size) {
  *compressed_size = snappy_max_compressed_length(uncompressed_size);
}

bool SnappyLibrary::Compress(char *uncompressed_data,
                             uint64_t uncompressed_size, char *compressed_data,
                             uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    snappy_status error = snappy_compress(uncompressed_data, uncompressed_size,
                                          compressed_data, compressed_size);
    if (SNAPPY_OK != error) {
      std::cout << "ERROR: snappy error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void SnappyLibrary::GetDecompressedDataSize(char *compressed_data,
                                            uint64_t compressed_size,
                                            uint64_t *decompressed_size) {
  snappy_uncompressed_length(compressed_data, compressed_size,
                             decompressed_size);
}

bool SnappyLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                               char *decompressed_data,
                               uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    snappy_status error = snappy_uncompress(
        compressed_data, compressed_size, decompressed_data, decompressed_size);
    if (SNAPPY_OK != error) {
      std::cout << "ERROR: snappy error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void SnappyLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "snappy", "A fast compressor/decompressor created by Google");
}

SnappyLibrary::SnappyLibrary() {}

SnappyLibrary::~SnappyLibrary() {}
