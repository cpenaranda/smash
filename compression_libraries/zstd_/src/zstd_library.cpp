/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <zstd.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <zstd_library.hpp>

bool ZstdLibrary::checkOptions(Options opt) {
  bool result{true};
  if (opt.getCompressionLevel() < 1) {
    std::cout << "ERROR: Compression level can not be higher than 1 using zstd"
              << std::endl;
    result = false;
  } else if (opt.getCompressionLevel() > 22) {
    std::cout << "ERROR: Compression level can not be higher than 22 using zstd"
              << std::endl;
    result = false;
  }
  return result;
}

void ZstdLibrary::getCompressDataSize(uint64_t uncompress_size,
                                      uint64_t *compress_size) {
  *compress_size = ZSTD_compressBound(uncompress_size);
}

bool ZstdLibrary::compress(Options opt, char *uncompress_data,
                           uint64_t uncompress_size, char *compress_data,
                           uint64_t *compress_size) {
  bool result = checkOptions(opt);
  if (result) {
    uint64_t new_size =
        ZSTD_compress(compress_data, *compress_size, uncompress_data,
                      uncompress_size, opt.getCompressionLevel());
    if (new_size > *compress_size) {
      std::cout << "ERROR: zstd error when compress data" << std::endl;
      result = false;
    }
    *compress_size = new_size;
  }
  return result;
}

bool ZstdLibrary::decompress(char *compress_data, uint64_t compress_size,
                             char *decompress_data, uint64_t *decompress_size) {
  bool result{true};
  uint64_t new_size = ZSTD_decompress(decompress_data, *decompress_size,
                                      compress_data, compress_size);
  if (new_size != *decompress_size) {
    std::cout << "ERROR: zstd error when decompress data" << std::endl;
    result = false;
  }
  *decompress_size = new_size;
  return result;
}

void ZstdLibrary::getTitle() {
  CompressionLibrary::getTitle(
      "zstd",
      "A fast lossless compression algorithm, targeting real-time compression "
      "scenarios at zlib-level and better compression ratios");
}

ZstdLibrary::ZstdLibrary() {}

ZstdLibrary::~ZstdLibrary() {}
