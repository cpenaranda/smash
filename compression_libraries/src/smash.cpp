/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

// SMASH LIBRARIES
#include <smash.hpp>
#include <compression_libraries.hpp>

void Smash::getCompressDataSize(uint64_t uncompress_size,
                                 uint64_t *compress_size) {
  lib->getCompressDataSize(uncompress_size, compress_size);
}

void Smash::compress(const Options &opt, char *uncompress_data,
                      uint64_t uncompress_size, char *compress_data,
                      uint64_t *compress_size) {
  lib->compress(opt, uncompress_data, uncompress_size, compress_data,
                compress_size);
}

void Smash::decompress(char *compress_data, uint64_t compress_size,
                        char *decompress_data, uint64_t *decompress_size) {
  lib->decompress(compress_data, compress_size, decompress_data,
                  decompress_size);
}

bool Smash::compareData(char *uncompress_data, const uint64_t &uncompress_size,
                         char *decompress_data,
                         const uint64_t &decompress_size) {
  return lib->compareData(uncompress_data, uncompress_size, decompress_data,
                          decompress_size);
}

Smash::Smash(const std::string &compression_library_name) {
  lib = CompressionLibraries().getCompressionLibrary(
      compression_library_name);
}

Smash::~Smash() { delete lib; }
