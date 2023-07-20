/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <lzfx.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <lzfx_library.hpp>

bool LzfxLibrary::Compress(const char *const uncompressed_data,
                           const uint64_t &uncompressed_data_size,
                           char *compressed_data,
                           uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    unsigned int lzfx_compressed_size = *compressed_data_size;
    int error = lzfx_compress(uncompressed_data, uncompressed_data_size,
                              compressed_data, &lzfx_compressed_size);
    if (error < 0) {
      std::cout << "ERROR: lzfx error when compress data" << std::endl;
      result = false;
    }
    *compressed_data_size = lzfx_compressed_size;
  }
  return result;
}

bool LzfxLibrary::Decompress(const char *const compressed_data,
                             const uint64_t &compressed_data_size,
                             char *decompressed_data,
                             uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    unsigned int lzfx_decompressed_size = *decompressed_data_size;
    int error = lzfx_decompress(compressed_data, compressed_data_size,
                                decompressed_data, &lzfx_decompressed_size);
    if (error < 0) {
      std::cout << "ERROR: lzfx error when decompress data" << std::endl;
      result = false;
    }
    *decompressed_data_size = lzfx_decompressed_size;
  }
  return result;
}

void LzfxLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle("lzfx",
                                  "Small library designed for very-high-speed "
                                  "compression of redundant data");
}

LzfxLibrary::LzfxLibrary() {}

LzfxLibrary::~LzfxLibrary() {}
