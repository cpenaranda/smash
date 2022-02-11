/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#pragma once

#include <iostream>
#include <string>

// SMASH LIBRARIES
#include <compression_library.hpp>
#include <options.hpp>

class BrieflzLibrary : public CompressionLibrary {
 private:
  bool checkOptions(Options opt);

 public:
  void getCompressDataSize(uint64_t uncompress_size, uint64_t *compress_size);

  bool compress(Options opt, char *uncompress_data, uint64_t uncompress_size,
                char *compress_data, uint64_t *compress_size);

  bool decompress(char *compress_data, uint64_t compress_size,
                  char *decompress_data, uint64_t *decompress_size);

  void getTitle();

  BrieflzLibrary();
  ~BrieflzLibrary();
};
