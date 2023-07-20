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

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <lzjb_library.hpp>

void LzjbLibrary::GetCompressedDataSize(const char *const uncompressed_data,
                                        const uint64_t &uncompressed_data_size,
                                        uint64_t *compressed_data_size) {
  *compressed_data_size = LZJB_MAX_COMPRESSED_SIZE(uncompressed_data_size);
}

bool LzjbLibrary::Compress(const char *const uncompressed_data,
                           const uint64_t &uncompressed_data_size,
                           char *compressed_data,
                           uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t bytes =
        lzjb_compress(reinterpret_cast<const uint8_t *const>(uncompressed_data),
                      reinterpret_cast<uint8_t *>(compressed_data),
                      uncompressed_data_size, *compressed_data_size);
    if (bytes == 0) {
      std::cout << "ERROR: lzjb error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_data_size = bytes;
    }
  }
  return result;
}

bool LzjbLibrary::Decompress(const char *const compressed_data,
                             const uint64_t &compressed_data_size,
                             char *decompressed_data,
                             uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    LZJBResult lzjb_result =
        lzjb_decompress(reinterpret_cast<const uint8_t *const>(compressed_data),
                        reinterpret_cast<uint8_t *>(decompressed_data),
                        compressed_data_size, decompressed_data_size);
    if (lzjb_result != LZJB_OK) {
      std::cout << "ERROR: lzjb error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void LzjbLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle("lzjb", "Created to compress data in ZFS");
}

LzjbLibrary::LzjbLibrary() {}

LzjbLibrary::~LzjbLibrary() {}
