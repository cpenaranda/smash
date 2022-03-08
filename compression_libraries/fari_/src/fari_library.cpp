/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <stddef.h>
// stddef is needed to compile correctly FastAri
#include <FastAri.h>

// SMASH LIBRARIES
#include <fari_library.hpp>
#include <options.hpp>

bool FariLibrary::SetOptionsCompressor(Options *options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) {
    options_ = *options;
    if (work_mem_decompression_) {
      delete[] work_mem_decompression_;
      work_mem_decompression_ = nullptr;
    }
    if (!work_mem_compression_) {
      work_mem_compression_ = new char[FA_WORKMEM];
    }
  }
  return initialized_compressor_;
}

bool FariLibrary::SetOptionsDecompressor(Options *options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) {
    options_ = *options;
    if (work_mem_compression_) {
      delete[] work_mem_compression_;
      work_mem_compression_ = nullptr;
    }
    if (!work_mem_decompression_) {
      work_mem_decompression_ = new char[FA_WORKMEM];
    }
  }
  return initialized_decompressor_;
}

bool FariLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                           char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    int fari_result = fa_compress(
        reinterpret_cast<unsigned char *>(uncompressed_data),
        reinterpret_cast<unsigned char *>(compressed_data),
        uncompressed_size +
            1 /*It is need because the last byte is not compressed in fari*/,
        compressed_size, work_mem_compression_);
    if (fari_result) {
      std::cout << "ERROR: fari error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool FariLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                             char *decompressed_data,
                             uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    int fari_result = fa_decompress(
        reinterpret_cast<unsigned char *>(compressed_data),
        reinterpret_cast<unsigned char *>(decompressed_data), compressed_size,
        decompressed_size, work_mem_decompression_);
    // It could return 2 because we incremente the uncompressed size by 1 to fix
    // a fari error where the last byte is not compressed
    if (fari_result != 2 && fari_result) {
      std::cout << "ERROR: fari error when decompress datas" << std::endl;
      result = false;
    }
  }
  return result;
}

void FariLibrary::GetTitle() {
  CompressionLibrary::GetTitle("fari",
                               "An arithmetic compressor with extremely high "
                               "compression/decompression speeds");
}

FariLibrary::FariLibrary() {
  work_mem_compression_ = nullptr;
  work_mem_decompression_ = nullptr;
}

FariLibrary::~FariLibrary() {
  if (work_mem_compression_) delete[] work_mem_compression_;
  if (work_mem_decompression_) delete[] work_mem_decompression_;
}
