/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <bzlib.h>

// SMASH LIBRARIES
#include <bzip2_library.hpp>
#include <options.hpp>

bool Bzip2Library::checkOptions(Options opt) {
  bool result{true};
  if (opt.getCompressionLevel() < 1) {
    std::cout << "ERROR: Compression level can not be lower than 1 using bzip2"
              << std::endl;
    result = false;
  } else if (opt.getCompressionLevel() > 9) {
    std::cout << "ERROR: Compression level can not be higher than 9 using bzip2"
              << std::endl;
    result = false;
  } else if (opt.getWorkFactor() > 250) {
    std::cout << "ERROR: Work factor can not be higher than 250 using bzip2"
              << std::endl;
    result = false;
  }
  return result;
}

void Bzip2Library::getCompressDataSize(uint64_t uncompress_size,
                                       uint64_t *compress_size) {
  *compress_size = ((uncompress_size / 5000) + 1) * 5000;
}

bool Bzip2Library::compress(Options opt, char *uncompress_data,
                            uint64_t uncompress_size, char *compress_data,
                            uint64_t *compress_size) {
  bool result = checkOptions(opt);
  if (result) {
    int bzerr = BZ2_bzBuffToBuffCompress(
        compress_data, reinterpret_cast<uint32_t *>(compress_size),
        uncompress_data, static_cast<uint32_t>(uncompress_size),
        opt.getCompressionLevel(), 0, opt.getWorkFactor());

    if (bzerr != BZ_OK && bzerr != BZ_OUTBUFF_FULL) {
      std::cout << "ERROR: bzip2 error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool Bzip2Library::decompress(char *compress_data, uint64_t compress_size,
                              char *decompress_data,
                              uint64_t *decompress_size) {
  bool result{true};
  int bzerr = BZ2_bzBuffToBuffDecompress(
      decompress_data, reinterpret_cast<uint32_t *>(decompress_size),
      compress_data, static_cast<uint32_t>(compress_size), 0, 0);
  if (bzerr != BZ_OK) {
    std::cout << "ERROR: bzip2 error when decompress data" << std::endl;
    result = false;
  }
  return result;
}

void Bzip2Library::getTitle() {
  CompressionLibrary::getTitle(
      "bzip2", "Based on Burrows-Wheeler algorithm and Huffman coding");
}

Bzip2Library::Bzip2Library() {}

Bzip2Library::~Bzip2Library() {}
