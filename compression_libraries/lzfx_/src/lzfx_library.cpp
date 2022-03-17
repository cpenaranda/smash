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

bool LzfxLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                           char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    unsigned int lzfx_compressed_size = *compressed_size;
    int error = lzfx_compress(uncompressed_data, uncompressed_size,
                              compressed_data, &lzfx_compressed_size);
    if (error < 0) {
      std::cout << "ERROR: lzfx error when compress data" << std::endl;
      result = false;
    }
    *compressed_size = lzfx_compressed_size;
  }
  return result;
}

bool LzfxLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                             char *decompressed_data,
                             uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    unsigned int lzfx_decompressed_size = *decompressed_size;
    int error = lzfx_decompress(compressed_data, compressed_size,
                                decompressed_data, &lzfx_decompressed_size);
    if (error < 0) {
      std::cout << "ERROR: lzfx error when decompress data" << std::endl;
      result = false;
    }
    *decompressed_size = lzfx_decompressed_size;
  }
  return result;
}

void LzfxLibrary::GetTitle() {
  CompressionLibrary::GetTitle("lzfx",
                               "Small library designed for very-high-speed "
                               "compression of redundant data");
}

LzfxLibrary::LzfxLibrary() {}

LzfxLibrary::~LzfxLibrary() {}
