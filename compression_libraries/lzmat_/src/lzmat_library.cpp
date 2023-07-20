/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <lzmat.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <lzmat_library.hpp>

void LzmatLibrary::GetCompressedDataSize(const char *const uncompressed_data,
                                         const uint64_t &uncompressed_data_size,
                                         uint64_t *compressed_data_size) {
  *compressed_data_size = MAX_LZMAT_ENCODED_SIZE(uncompressed_data_size);
}

bool LzmatLibrary::Compress(const char *const uncompressed_data,
                            const uint64_t &uncompressed_data_size,
                            char *compressed_data,
                            uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    int lzmat_result = lzmat_encode(
        reinterpret_cast<MP_U8 *>(compressed_data),
        reinterpret_cast<MP_U32 *>(compressed_data_size),
        const_cast<MP_U8 *>(
            reinterpret_cast<const MP_U8 *const>(uncompressed_data)),
        static_cast<MP_U32>(uncompressed_data_size));
    if (lzmat_result) {
      std::cout << "ERROR: lzmat error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool LzmatLibrary::Decompress(const char *const compressed_data,
                              const uint64_t &compressed_data_size,
                              char *decompressed_data,
                              uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    int lzmat_result =
        lzmat_decode(reinterpret_cast<MP_U8 *>(decompressed_data),
                     reinterpret_cast<MP_U32 *>(decompressed_data_size),
                     const_cast<MP_U8 *>(
                         reinterpret_cast<const MP_U8 *const>(compressed_data)),
                     static_cast<MP_U32>(compressed_data_size));
    if (lzmat_result) {
      std::cout << "ERROR: lzmat error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void LzmatLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle(
      "lzmat",
      "Extremely fast real-time lossless data compression library (requires no "
      "memory for decompression)");
}

LzmatLibrary::LzmatLibrary() {}

LzmatLibrary::~LzmatLibrary() {}
