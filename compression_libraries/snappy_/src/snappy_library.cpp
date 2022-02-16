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

bool SnappyLibrary::checkOptions(Options opt) {
  bool result{true};
  return result;
}

void SnappyLibrary::getCompressDataSize(uint64_t uncompress_size,
                                        uint64_t *compress_size) {
  *compress_size = snappy_max_compressed_length(uncompress_size);
}

bool SnappyLibrary::compress(Options opt, char *uncompress_data,
                             uint64_t uncompress_size, char *compress_data,
                             uint64_t *compress_size) {
  bool result = checkOptions(opt);
  if (result) {
    snappy_status error = snappy_compress(uncompress_data, uncompress_size,
                                          compress_data, compress_size);
    if (SNAPPY_OK != error) {
      std::cout << "ERROR: snappy error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool SnappyLibrary::decompress(char *compress_data, uint64_t compress_size,
                               char *decompress_data,
                               uint64_t *decompress_size) {
  bool result{true};
  snappy_status error = snappy_uncompress(compress_data, compress_size,
                                          decompress_data, decompress_size);
  if (SNAPPY_OK != error) {
    std::cout << "ERROR: snappy error when decompress data" << std::endl;
    result = false;
  }
  return result;
}

void SnappyLibrary::getTitle() {
  CompressionLibrary::getTitle(
      "snappy", "A fast compressor/decompressor created by Google");
}

SnappyLibrary::SnappyLibrary() {}

SnappyLibrary::~SnappyLibrary() {}
