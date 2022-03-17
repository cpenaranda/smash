/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <quicklz.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <quicklz_library.hpp>

void QuicklzLibrary::GetCompressedDataSize(char *uncompressed_data,
                                           uint64_t uncompressed_size,
                                           uint64_t *compressed_size) {
  *compressed_size = qlz_size_compressed(uncompressed_data);
}

bool QuicklzLibrary::Compress(char *uncompressed_data,
                              uint64_t uncompressed_size, char *compressed_data,
                              uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    qlz_state_compress state;
    uint64_t final_size = qlz_compress(uncompressed_data, compressed_data,
                                       uncompressed_size, &state);
    if (final_size == 0) {
      std::cout << "ERROR: quicklz error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_size = final_size;
    }
  }
  return result;
}

bool QuicklzLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                                char *decompressed_data,
                                uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    qlz_state_decompress state;
    uint64_t final_size =
        qlz_decompress(compressed_data, decompressed_data, &state);
    if (final_size == 0) {
      std::cout << "ERROR: quicklz error when decompress data" << std::endl;
      result = false;
    } else {
      *decompressed_size = final_size;
    }
  }
  return result;
}

void QuicklzLibrary::GetDecompressedDataSize(char *compressed_data,
                                             uint64_t compressed_size,
                                             uint64_t *decompressed_size) {
  *decompressed_size = qlz_size_decompressed(compressed_data);
}

void QuicklzLibrary::GetTitle() {
  CompressionLibrary::GetTitle("quicklz", "Fast GPL'd compression library.");
}

QuicklzLibrary::QuicklzLibrary() {}

QuicklzLibrary::~QuicklzLibrary() {}
