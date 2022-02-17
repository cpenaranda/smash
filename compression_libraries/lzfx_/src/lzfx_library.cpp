/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <lzfx.h>

// SMASH LIBRARIES
#include <lzfx_library.hpp>
#include <options.hpp>

bool LzfxLibrary::checkOptions(Options opt) {
  bool result{true};
  return result;
}

void LzfxLibrary::getCompressDataSize(uint64_t uncompress_size,
                                      uint64_t *compress_size) {
  *compress_size = ((uncompress_size / 5000) + 1) * 5000;
}

bool LzfxLibrary::compress(Options opt, char *uncompress_data,
                           uint64_t uncompress_size, char *compress_data,
                           uint64_t *compress_size) {
  bool result = checkOptions(opt);
  if (result) {
    unsigned int lzfx_compressed_size = *compress_size;
    int error = lzfx_compress(uncompress_data, uncompress_size, compress_data,
                              &lzfx_compressed_size);
    if (error < 0) {
      std::cout << "ERROR: lzfx error when compress data" << std::endl;
      result = false;
    }
    *compress_size = lzfx_compressed_size;
  }
  return result;
}

bool LzfxLibrary::decompress(char *compress_data, uint64_t compress_size,
                             char *decompress_data, uint64_t *decompress_size) {
  bool result{true};
  unsigned int lzfx_decompressed_size = *decompress_size;
  int error = lzfx_decompress(compress_data, compress_size, decompress_data,
                              &lzfx_decompressed_size);
  if (error < 0) {
    std::cout << "ERROR: lzfx error when decompress data" << std::endl;
    result = false;
  }
  *decompress_size = lzfx_decompressed_size;
  return result;
}

void LzfxLibrary::getTitle() {
  CompressionLibrary::getTitle("lzfx",
                               "A small BSD-licensed library designed for "
                               "very-high-speed compression of redundant data");
}

LzfxLibrary::LzfxLibrary() {}

LzfxLibrary::~LzfxLibrary() {}
