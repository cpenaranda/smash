/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <lzfse.h>

// SMASH LIBRARIES
#include <lzfse_library.hpp>
#include <options.hpp>

bool LzfseLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                            char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    char *workmem = new char[lzfse_encode_scratch_size()];
    uint64_t final_compression_size = lzfse_encode_buffer(
        reinterpret_cast<uint8_t *>(compressed_data), *compressed_size,
        reinterpret_cast<uint8_t *>(uncompressed_data), uncompressed_size,
        workmem);
    if (final_compression_size == 0) {
      std::cout << "ERROR: lzfse error when compress data" << std::endl;
      result = false;
    }
    delete[] workmem;
    *compressed_size = final_compression_size;
  }
  return result;
}

bool LzfseLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                              char *decompressed_data,
                              uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    char *workmem = new char[lzfse_decode_scratch_size()];
    uint64_t final_decompression_size = lzfse_decode_buffer(
        reinterpret_cast<uint8_t *>(decompressed_data), *decompressed_size,
        reinterpret_cast<uint8_t *>(compressed_data), compressed_size, workmem);
    if (final_decompression_size != *decompressed_size) {
      std::cout << "ERROR: lzfse error when decompress data" << std::endl;
      result = false;
    }
    delete[] workmem;
  }
  return result;
}

void LzfseLibrary::GetTitle() {
  CompressionLibrary::GetTitle("lzfse",
                               "A Lempel-Ziv style data compression algorithm "
                               "using Finite State Entropy coding");
}

LzfseLibrary::LzfseLibrary() {}

LzfseLibrary::~LzfseLibrary() {}
