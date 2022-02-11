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
#include <options.hpp>

class CompressionLibrary {
 public:
  virtual void getCompressDataSize(uint64_t uncompress_size,
                                   uint64_t *compress_size) = 0;

  virtual bool compress(Options opt, char *uncompress_data,
                        uint64_t uncompress_size, char *compress_data,
                        uint64_t *compress_size) = 0;

  virtual bool decompress(char *compress_data, uint64_t compress_size,
                          char *decompress_data, uint64_t *decompress_size) = 0;

  virtual void getTitle() = 0;

  void getTitle(const std::string &library_name,
                const std::string &description);

  bool compareData(char *uncompress_data, const uint64_t &uncompress_size,
                   char *decompress_data, const uint64_t &decompress_size);

  CompressionLibrary();
  virtual ~CompressionLibrary();
};
