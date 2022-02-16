/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <mscomp.h>

// SMASH LIBRARIES
#include <ms_library.hpp>
#include <options.hpp>

bool MsLibrary::checkOptions(Options opt) {
  bool result{true};
  if (opt.getMode() > 2) {
    std::cout << "ERROR: Mode can not be higher than 2 using ms" << std::endl;
    result = false;
  }
  return result;
}

void MsLibrary::getCompressDataSize(uint64_t uncompress_size,
                                    uint64_t *compress_size) {
  // *compress_size = ms_max_compressed_size (format_, uncompress_size);
  *compress_size = ((uncompress_size / 5000) + 1) * 5000;
}

bool MsLibrary::compress(Options opt, char *uncompress_data,
                         uint64_t uncompress_size, char *compress_data,
                         uint64_t *compress_size) {
  bool result = checkOptions(opt);
  if (result) {
    switch (opt.getMode()) {
      case 0:
        format_ = MSCOMP_LZNT1;
        break;
      case 1:
        format_ = MSCOMP_XPRESS;
        break;
      case 2:
        format_ = MSCOMP_XPRESS_HUFF;
        break;
      default:
        break;
    }
    MSCompStatus error = ms_compress(
        format_, reinterpret_cast<bytes>(uncompress_data), uncompress_size,
        reinterpret_cast<bytes>(compress_data), compress_size);
    if (error != MSCOMP_OK) {
      std::cout << "ERROR: ms error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool MsLibrary::decompress(char *compress_data, uint64_t compress_size,
                           char *decompress_data, uint64_t *decompress_size) {
  bool result{true};
  MSCompStatus error = ms_decompress(
      format_, reinterpret_cast<bytes>(compress_data), compress_size,
      reinterpret_cast<bytes>(decompress_data), decompress_size);
  if (error != MSCOMP_OK) {
    std::cout << "ERROR: ms error when decompress data" << std::endl;
    result = false;
  }
  return result;
}

void MsLibrary::getTitle() {
  CompressionLibrary::getTitle(
      "ms", "Open source implementations of Microsoft compression algorithms");
}

MsLibrary::MsLibrary() {}

MsLibrary::~MsLibrary() {}
