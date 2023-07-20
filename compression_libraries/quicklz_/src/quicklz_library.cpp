/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <quicklz.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <quicklz_library.hpp>

void QuicklzLibrary::GetCompressedDataSize(
    const char *const uncompressed_data, const uint64_t &uncompressed_data_size,
    uint64_t *compressed_data_size) {
  if (uncompressed_data) {
    *compressed_data_size = qlz_size_compressed(uncompressed_data);
  } else {
    CpuCompressionLibrary::GetCompressedDataSize(
        uncompressed_data, uncompressed_data_size, compressed_data_size);
  }
}

bool QuicklzLibrary::Compress(const char *const uncompressed_data,
                              const uint64_t &uncompressed_data_size,
                              char *compressed_data,
                              uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    qlz_state_compress state;
    uint64_t final_size = qlz_compress(uncompressed_data, compressed_data,
                                       uncompressed_data_size, &state);
    if (final_size == 0) {
      std::cout << "ERROR: quicklz error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_data_size = final_size;
    }
  }
  return result;
}

bool QuicklzLibrary::Decompress(const char *const compressed_data,
                                const uint64_t &compressed_data_size,
                                char *decompressed_data,
                                uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    qlz_state_decompress state;
    uint64_t final_size =
        qlz_decompress(compressed_data, decompressed_data, &state);
    if (final_size == 0) {
      std::cout << "ERROR: quicklz error when decompress data" << std::endl;
      result = false;
    } else {
      *decompressed_data_size = final_size;
    }
  }
  return result;
}

void QuicklzLibrary::GetDecompressedDataSize(
    const char *const compressed_data, const uint64_t &compressed_data_size,
    uint64_t *decompressed_data_size) {
  *decompressed_data_size = qlz_size_decompressed(compressed_data);
}

void QuicklzLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle("quicklz", "Fast GPL'd compression library.");
}

QuicklzLibrary::QuicklzLibrary() {}

QuicklzLibrary::~QuicklzLibrary() {}
