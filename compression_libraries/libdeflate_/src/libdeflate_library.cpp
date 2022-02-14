/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <libdeflate.h>

// SMASH LIBRARIES
#include <libdeflate_library.hpp>
#include <options.hpp>

bool LibdeflateLibrary::checkOptions(Options opt) {
  bool result{true};
  if (opt.getCompressionLevel() > 12) {
    std::cout
        << "ERROR: Compression level can not be higher than 12 using libdeflate"
        << std::endl;
    result = false;
  }
  return result;
}

void LibdeflateLibrary::getCompressDataSize(uint64_t uncompress_size,
                                            uint64_t *compress_size) {
  *compress_size = libdeflate_deflate_compress_bound(NULL, uncompress_size);
}

bool LibdeflateLibrary::compress(Options opt, char *uncompress_data,
                                 uint64_t uncompress_size, char *compress_data,
                                 uint64_t *compress_size) {
  bool result = checkOptions(opt);
  if (result) {
    struct libdeflate_compressor *compressor =
        libdeflate_alloc_compressor(opt.getCompressionLevel());
    *compress_size = libdeflate_deflate_compress(compressor, uncompress_data,
                                                 uncompress_size, compress_data,
                                                 *compress_size);
    libdeflate_free_compressor(compressor);
    if (compress_size == 0) {
      std::cout << "ERROR: libdeflate error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool LibdeflateLibrary::decompress(char *compress_data, uint64_t compress_size,
                                   char *decompress_data,
                                   uint64_t *decompress_size) {
  bool result{true};
  struct libdeflate_decompressor *decompressor =
      libdeflate_alloc_decompressor();
  uint64_t bytes{0};
  enum libdeflate_result res =
      libdeflate_deflate_decompress(decompressor, compress_data, compress_size,
                                    decompress_data, *decompress_size, &bytes);
  libdeflate_free_decompressor(decompressor);
  *decompress_size = bytes;
  if (res != LIBDEFLATE_SUCCESS) {
    std::cout << "ERROR: libdeflate error when decompress data" << std::endl;
    result = false;
  }
  return result;
}

void LibdeflateLibrary::getTitle() {
  CompressionLibrary::getTitle(
      "libdeflate",
      "Fast, whole-buffer DEFLATE-based compression and decompression");
}

LibdeflateLibrary::LibdeflateLibrary() {}

LibdeflateLibrary::~LibdeflateLibrary() {}
