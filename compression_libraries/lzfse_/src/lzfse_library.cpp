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

bool LzfseLibrary::checkOptions(Options opt) {
  bool result{true};
  return result;
}

void LzfseLibrary::getCompressDataSize(uint64_t uncompress_size,
                                       uint64_t *compress_size) {
  *compress_size = ((uncompress_size / 5000) + 1) * 5000;
}

bool LzfseLibrary::compress(Options opt, char *uncompress_data,
                            uint64_t uncompress_size, char *compress_data,
                            uint64_t *compress_size) {
  bool result = checkOptions(opt);
  if (result) {
    char *workmem = new char[lzfse_encode_scratch_size()];
    uint64_t final_compression_size = lzfse_encode_buffer(
        reinterpret_cast<uint8_t *>(compress_data), *compress_size,
        reinterpret_cast<uint8_t *>(uncompress_data), uncompress_size, workmem);
    if (final_compression_size == 0) {
      std::cout << "ERROR: lzfse error when compress data" << std::endl;
      result = false;
    }
    delete[] workmem;
    *compress_size = final_compression_size;
  }
  return result;
}

bool LzfseLibrary::decompress(char *compress_data, uint64_t compress_size,
                              char *decompress_data,
                              uint64_t *decompress_size) {
  bool result{true};
  char *workmem = new char[lzfse_decode_scratch_size()];
  uint64_t final_decompression_size = lzfse_decode_buffer(
      reinterpret_cast<uint8_t *>(decompress_data), *decompress_size,
      reinterpret_cast<uint8_t *>(compress_data), compress_size, workmem);
  if (final_decompression_size != *decompress_size) {
    std::cout << "ERROR: lzfse error when decompress data" << std::endl;
    result = false;
  }
  delete[] workmem;
  return result;
}

void LzfseLibrary::getTitle() {
  CompressionLibrary::getTitle("lzfse",
                               "A Lempel-Ziv style data compression algorithm "
                               "using Finite State Entropy coding");
}

LzfseLibrary::LzfseLibrary() {}

LzfseLibrary::~LzfseLibrary() {}
