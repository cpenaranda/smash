/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <libxpack.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <xpack_library.hpp>

bool XpackLibrary::checkOptions(Options opt) {
  bool result{true};
  if (opt.getCompressionLevel() < 1) {
    std::cout << "ERROR: Compression level can not be lower than 1 using xpack"
              << std::endl;
    result = false;
  } else if (opt.getCompressionLevel() > 9) {
    std::cout << "ERROR: Compression level can not be higher than 9 using xpack"
              << std::endl;
    result = false;
  }
  return result;
}

void XpackLibrary::getCompressDataSize(uint64_t uncompress_size,
                                       uint64_t *compress_size) {
  *compress_size = ((uncompress_size / 5000) + 1) * 5000;
}

bool XpackLibrary::compress(Options opt, char *uncompress_data,
                            uint64_t uncompress_size, char *compress_data,
                            uint64_t *compress_size) {
  bool result = checkOptions(opt);
  if (result) {
    xpack_compressor *compressor =
        xpack_alloc_compressor(uncompress_size, opt.getCompressionLevel());
    *compress_size =
        xpack_compress(compressor, uncompress_data, uncompress_size,
                       compress_data, *compress_size);
    if (!*compress_size) {
      std::cout << "ERROR: xpack error when compress data" << std::endl;
      result = false;
    }
    xpack_free_compressor(compressor);
  }
  return result;
}

bool XpackLibrary::decompress(char *compress_data, uint64_t compress_size,
                              char *decompress_data,
                              uint64_t *decompress_size) {
  bool result{true};
  xpack_decompressor *decompressor = xpack_alloc_decompressor();
  uint64_t uncompress_size{0};
  decompress_result error =
      xpack_decompress(decompressor, compress_data, compress_size,
                       decompress_data, *decompress_size, &uncompress_size);
  if (error != DECOMPRESS_SUCCESS || uncompress_size != *decompress_size) {
    std::cout << "ERROR: xpack error when decompress data" << std::endl;
    result = false;
  }
  xpack_free_decompressor(decompressor);
  return result;
}

void XpackLibrary::getTitle() {
  CompressionLibrary::getTitle("xpack",
                               "Has been inspired by the DEFLATE, LZX, and "
                               "Zstandard formats, among others");
}

XpackLibrary::XpackLibrary() {}

XpackLibrary::~XpackLibrary() {}
