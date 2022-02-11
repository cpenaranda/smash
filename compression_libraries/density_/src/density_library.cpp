/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <density_api.h>

// SMASH LIBRARIES
#include <density_library.hpp>
#include <options.hpp>

bool DensityLibrary::checkOptions(Options opt) {
  bool result{true};
  if (opt.getCompressionLevel() < 1) {
    std::cout
        << "ERROR: Compression level can not be lower than 1 using density"
        << std::endl;
    result = false;
  } else if (opt.getCompressionLevel() > 3) {
    std::cout
        << "ERROR: Compression level can not be higher than 3 using density"
        << std::endl;
    result = false;
  }
  return result;
}

void DensityLibrary::getCompressDataSize(uint64_t uncompress_size,
                                         uint64_t *compress_size) {
  *compress_size = density_compress_safe_size(uncompress_size);
}

bool DensityLibrary::compress(Options opt, char *uncompress_data,
                              uint64_t uncompress_size, char *compress_data,
                              uint64_t *compress_size) {
  bool result = checkOptions(opt);
  if (result) {
    DENSITY_ALGORITHM alg;
    switch (opt.getCompressionLevel()) {
      case 1:
        alg = DENSITY_ALGORITHM::DENSITY_ALGORITHM_CHAMELEON;
        break;
      case 2:
        alg = DENSITY_ALGORITHM::DENSITY_ALGORITHM_CHEETAH;
        break;
      case 3:
        alg = DENSITY_ALGORITHM::DENSITY_ALGORITHM_LION;
        break;
      default:
        break;
    }
    density_processing_result res = density_compress(
        reinterpret_cast<uint8_t *>(uncompress_data), uncompress_size,
        reinterpret_cast<uint8_t *>(compress_data), *compress_size, alg);
    if (res.state || res.bytesWritten > *compress_size) {
      std::cout << "ERROR: density error when compress data" << std::endl;
      result = false;
    }
    *compress_size = res.bytesWritten;
  }
  return result;
}

bool DensityLibrary::decompress(char *compress_data, uint64_t compress_size,
                                char *decompress_data,
                                uint64_t *decompress_size) {
  bool result{true};
  density_processing_result res = density_decompress(
      reinterpret_cast<uint8_t *>(compress_data), compress_size,
      reinterpret_cast<uint8_t *>(decompress_data),
      density_decompress_safe_size(*decompress_size));
  if (res.state || res.bytesWritten != *decompress_size) {
    std::cout << "ERROR: density error when decompress data" << std::endl;
    result = false;
  }
  return result;
}

void DensityLibrary::getTitle() {
  CompressionLibrary::getTitle("density", "Superfast compression library");
}

DensityLibrary::DensityLibrary() {}

DensityLibrary::~DensityLibrary() {}
