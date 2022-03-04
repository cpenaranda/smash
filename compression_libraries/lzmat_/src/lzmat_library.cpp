/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <lzmat.h>

// SMASH LIBRARIES
#include <lzmat_library.hpp>
#include <options.hpp>

void LzmatLibrary::GetCompressedDataSize(char *uncompressed_data,
                                         uint64_t uncompressed_size,
                                         uint64_t *compressed_size) {
  *compressed_size = MAX_LZMAT_ENCODED_SIZE(uncompressed_size);
}

bool LzmatLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                            char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    int lzmat_result =
        lzmat_encode(reinterpret_cast<MP_U8 *>(compressed_data),
                     reinterpret_cast<MP_U32 *>(compressed_size),
                     reinterpret_cast<MP_U8 *>(uncompressed_data),
                     static_cast<MP_U32>(uncompressed_size));
    if (lzmat_result) {
      std::cout << "ERROR: lzmat error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool LzmatLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                              char *decompressed_data,
                              uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    int lzmat_result =
        lzmat_decode(reinterpret_cast<MP_U8 *>(decompressed_data),
                     reinterpret_cast<MP_U32 *>(decompressed_size),
                     reinterpret_cast<MP_U8 *>(compressed_data),
                     static_cast<MP_U32>(compressed_size));
    if (lzmat_result) {
      std::cout << "ERROR: lzmat error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void LzmatLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "lzmat", "An extremely fast real-time lossless data compression library");
}

LzmatLibrary::LzmatLibrary() {}

LzmatLibrary::~LzmatLibrary() {}
