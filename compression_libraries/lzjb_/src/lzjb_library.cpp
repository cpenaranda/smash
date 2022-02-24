/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

extern "C" {
#include <lzjb.h>
}

// SMASH LIBRARIES
#include <lzjb_library.hpp>
#include <options.hpp>

void LzjbLibrary::GetCompressedDataSize(char *uncompressed_data,
                                        uint64_t uncompressed_size,
                                        uint64_t *compressed_size) {
  *compressed_size = LZJB_MAX_COMPRESSED_SIZE(uncompressed_size);
}

bool LzjbLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                           char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t bytes =
        lzjb_compress(reinterpret_cast<uint8_t *>(uncompressed_data),
                      reinterpret_cast<uint8_t *>(compressed_data),
                      uncompressed_size, *compressed_size);
    if (bytes == 0) {
      std::cout << "ERROR: lzjb error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_size = bytes;
    }
  }
  return result;
}

bool LzjbLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                             char *decompressed_data,
                             uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    LZJBResult lzjb_result =
        lzjb_decompress(reinterpret_cast<uint8_t *>(compressed_data),
                        reinterpret_cast<uint8_t *>(decompressed_data),
                        compressed_size, decompressed_size);
    if (lzjb_result != LZJB_OK) {
      std::cout << "ERROR: lzjb error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void LzjbLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "lzjb",
      "A compression codec originally created to compress data in ZFS.");
}

LzjbLibrary::LzjbLibrary() {}

LzjbLibrary::~LzjbLibrary() {}
