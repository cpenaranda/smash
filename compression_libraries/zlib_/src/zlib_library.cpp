/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <zlib.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <zlib_library.hpp>

bool ZlibLibrary::checkOptions(Options opt) {
  bool result{true};
  if (opt.getCompressionLevel() > 9) {
    std::cout
        << "ERROR: Compression level can not be higher than 9 using zlib"
        << std::endl;
    result = false;
  }
  return result;
}

void ZlibLibrary::getCompressDataSize(uint64_t uncompress_size,
                                      uint64_t *compress_size) {
  *compress_size = compressBound(uncompress_size);
}

bool ZlibLibrary::compress(Options opt, char *uncompress_data,
                           uint64_t uncompress_size, char *compress_data,
                           uint64_t *compress_size) {
  bool result = checkOptions(opt);
  if (result) {
    int err = compress2(reinterpret_cast<Bytef *>(compress_data), compress_size,
                        reinterpret_cast<Bytef *>(uncompress_data),
                        uncompress_size, opt.getCompressionLevel());
    if (err != Z_OK) {
      std::cout << "ERROR: zlib error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool ZlibLibrary::decompress(char *compress_data, uint64_t compress_size,
                             char *decompress_data, uint64_t *decompress_size) {
  bool result{true};
  int err =
      uncompress(reinterpret_cast<Bytef *>(decompress_data), decompress_size,
                 reinterpret_cast<Bytef *>(compress_data), compress_size);
  if (err != Z_OK) {
    std::cout << "ERROR: zlib error when decompress data" << std::endl;
    result = false;
  }
  return result;
}

void ZlibLibrary::getTitle() {
  CompressionLibrary::getTitle("zlib",
                               "A general purpose data compression library");
}

ZlibLibrary::ZlibLibrary() {}

ZlibLibrary::~ZlibLibrary() {}
