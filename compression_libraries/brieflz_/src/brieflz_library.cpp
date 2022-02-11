/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <brieflz.h>

// SMASH LIBRARIES
#include <brieflz_library.hpp>
#include <options.hpp>

bool BrieflzLibrary::checkOptions(Options opt) {
  bool result{true};
  if (opt.getCompressionLevel() < 1) {
    std::cout
        << "ERROR: Compression level can not be lower than 1 using brieflz"
        << std::endl;
    result = false;
  } else if (opt.getCompressionLevel() > 10) {
    std::cout
        << "ERROR: Compression level can not be higher than 10 using brieflz"
        << std::endl;
    result = false;
  }
  return result;
}

void BrieflzLibrary::getCompressDataSize(uint64_t uncompress_size,
                                         uint64_t *compress_size) {
  *compress_size = blz_max_packed_size(uncompress_size);
}

bool BrieflzLibrary::compress(Options opt, char *uncompress_data,
                              uint64_t uncompress_size, char *compress_data,
                              uint64_t *compress_size) {
  bool result = checkOptions(opt);
  if (result) {
    char *workmem = new char[blz_workmem_size_level(uncompress_size,
                                                    opt.getCompressionLevel())];
    uint64_t final_compression_size{0};
    final_compression_size =
        blz_pack_level(uncompress_data, compress_data, uncompress_size, workmem,
                       opt.getCompressionLevel());
    if (final_compression_size == BLZ_ERROR ||
        final_compression_size > *compress_size) {
      std::cout << "ERROR: brieflz error when compress data" << std::endl;
      result = false;
    }
    delete[] workmem;
    *compress_size = final_compression_size;
  }
  return result;
}

bool BrieflzLibrary::decompress(char *compress_data, uint64_t compress_size,
                                char *decompress_data,
                                uint64_t *decompress_size) {
  bool result{true};
  uint64_t final_decompression_size{0};
  final_decompression_size = blz_depack_safe(compress_data, compress_size,
                                             decompress_data, *decompress_size);
  if (final_decompression_size != *decompress_size) {
    std::cout << "ERROR: brieflz error when decompress data" << std::endl;
    result = false;
  }
  return result;
}

void BrieflzLibrary::getTitle() {
  CompressionLibrary::getTitle("brieflz",
                               "Fast Lempel-Ziv compression library");
}

BrieflzLibrary::BrieflzLibrary() {}

BrieflzLibrary::~BrieflzLibrary() {}
