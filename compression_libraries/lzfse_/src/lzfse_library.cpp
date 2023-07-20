/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <lzfse.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <lzfse_library.hpp>

bool LzfseLibrary::Compress(const char *const uncompressed_data,
                            const uint64_t &uncompressed_data_size,
                            char *compressed_data,
                            uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    char *workmem = new char[lzfse_encode_scratch_size()];
    uint64_t final_compression_size = lzfse_encode_buffer(
        reinterpret_cast<uint8_t *>(compressed_data), *compressed_data_size,
        reinterpret_cast<const uint8_t *const>(uncompressed_data),
        uncompressed_data_size, workmem);
    if (final_compression_size == 0) {
      std::cout << "ERROR: lzfse error when compress data" << std::endl;
      result = false;
    }
    delete[] workmem;
    *compressed_data_size = final_compression_size;
  }
  return result;
}

bool LzfseLibrary::Decompress(const char *const compressed_data,
                              const uint64_t &compressed_data_size,
                              char *decompressed_data,
                              uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    char *workmem = new char[lzfse_decode_scratch_size()];
    uint64_t final_decompression_size = lzfse_decode_buffer(
        reinterpret_cast<uint8_t *>(decompressed_data), *decompressed_data_size,
        reinterpret_cast<const uint8_t *const>(compressed_data),
        compressed_data_size, workmem);
    if (final_decompression_size != *decompressed_data_size) {
      std::cout << "ERROR: lzfse error when decompress data" << std::endl;
      result = false;
    }
    delete[] workmem;
  }
  return result;
}

void LzfseLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle("lzfse",
                                  "LZ77 style data compression algorithm "
                                  "using Finite State Entropy coding");
}

LzfseLibrary::LzfseLibrary() {}

LzfseLibrary::~LzfseLibrary() {}
