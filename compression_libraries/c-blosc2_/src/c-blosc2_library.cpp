/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <blosc2.h>

// SMASH LIBRARIES
#include <c-blosc2_library.hpp>
#include <options.hpp>

bool CBlosc2Library::checkOptions(Options opt) {
  bool result{true};
  if (opt.getCompressionLevel() > 9) {
    std::cout
        << "ERROR: Compression level can not be higher than 9 using c-blosc2"
        << std::endl;
    result = false;
  } else if (opt.getShuffle() > 2) {
    std::cout << "ERROR: Shuffle value can not be higher than 2 using c-blosc2"
              << std::endl;
    result = false;
  } else if (opt.getNumberThreads() < 1) {
    std::cout << "ERROR: Number of threads must be higher than 1 using c-blosc2"
              << std::endl;
    result = false;
  }
  return result;
}

void CBlosc2Library::getCompressDataSize(uint64_t uncompress_size,
                                         uint64_t *compress_size) {
  *compress_size = uncompress_size + BLOSC_MAX_OVERHEAD;
}

bool CBlosc2Library::compress(Options opt, char *uncompress_data,
                              uint64_t uncompress_size, char *compress_data,
                              uint64_t *compress_size) {
  bool result = checkOptions(opt);
  if (result) {
    blosc_set_nthreads(opt.getNumberThreads());
    int csize = blosc_compress(opt.getCompressionLevel(), opt.getShuffle(),
                               sizeof(char), uncompress_size, uncompress_data,
                               compress_data, *compress_size);
    if (csize == 0 || csize < 0) {
      std::cout << "ERROR: c-blosc2 error when compress data" << std::endl;
      result = false;
    }
    *compress_size = static_cast<uint64_t>(csize);
  }
  return result;
}

bool CBlosc2Library::decompress(char *compress_data, uint64_t compress_size,
                                char *decompress_data,
                                uint64_t *decompress_size) {
  bool result{true};
  int dsize =
      blosc_decompress(compress_data, decompress_data, *decompress_size);
  if (dsize < 0) {
    std::cout << "ERROR: c-blosc2 error when decompress data" << std::endl;
    result = false;
  }
  *decompress_size = static_cast<uint64_t>(dsize);
  return result;
}

void CBlosc2Library::getTitle() {
  CompressionLibrary::getTitle(
      "c-blosc2", "High performance compressor optimized for binary data");
}

CBlosc2Library::CBlosc2Library() {
  blosc_init();
  blosc_set_compressor("blosclz");
}

CBlosc2Library::~CBlosc2Library() { blosc_destroy(); }
