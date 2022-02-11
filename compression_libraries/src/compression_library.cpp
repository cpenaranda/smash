/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <string.h>

#include <iomanip>

// SMASH LIBRARIES
#include <compression_library.hpp>

void CompressionLibrary::getTitle(const std::string &library_name,
                                  const std::string &description) {
  std::cout << std::left << std::setw(15) << std::setfill(' ') << library_name
            << "- " << description << std::endl;
}

bool CompressionLibrary::compareData(char *uncompress_data,
                                     const uint64_t &uncompress_size,
                                     char *decompress_data,
                                     const uint64_t &decompress_size) {
  return ((uncompress_size == decompress_size) &&
          (memcmp(uncompress_data, decompress_data, decompress_size) == 0));
}

CompressionLibrary::CompressionLibrary() {}
CompressionLibrary::~CompressionLibrary() {}
