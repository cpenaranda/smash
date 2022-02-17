/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <zlib-ng.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <zlib-ng_library.hpp>

bool ZlibNgLibrary::checkOptions(Options opt) {
  bool result{true};
  if (opt.getCompressionLevel() > 9) {
    std::cout
        << "ERROR: Compression level can not be higher than 9 using zlib-ng"
        << std::endl;
    result = false;
  }
  return result;
}

void ZlibNgLibrary::getCompressDataSize(uint64_t uncompress_size,
                                        uint64_t *compress_size) {
  *compress_size = zng_compressBound(uncompress_size);
}

bool ZlibNgLibrary::compress(Options opt, char *uncompress_data,
                             uint64_t uncompress_size, char *compress_data,
                             uint64_t *compress_size) {
  bool result = checkOptions(opt);
  if (result) {
    int err =
        zng_compress2(reinterpret_cast<Bytef *>(compress_data), compress_size,
                      reinterpret_cast<Bytef *>(uncompress_data),
                      uncompress_size, opt.getCompressionLevel());
    if (err != Z_OK) {
      std::cout << "ERROR: zlib-ng error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool ZlibNgLibrary::decompress(char *compress_data, uint64_t compress_size,
                               char *decompress_data,
                               uint64_t *decompress_size) {
  bool result{true};
  int err = zng_uncompress2(
      reinterpret_cast<Bytef *>(decompress_data), decompress_size,
      reinterpret_cast<Bytef *>(compress_data), &compress_size);
  if (err != Z_OK) {
    std::cout << "ERROR: zlib-ng error when decompress data" << std::endl;
    result = false;
  }
  return result;
}

void ZlibNgLibrary::getTitle() {
  CompressionLibrary::getTitle("zlib-ng",
                               "zlib for the next generation systems");
}

ZlibNgLibrary::ZlibNgLibrary() {}

ZlibNgLibrary::~ZlibNgLibrary() {}
