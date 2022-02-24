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
#include <vector>

// SMASH LIBRARIES
#include <compression_library.hpp>
#include <options.hpp>

class Z3libLibrary : public CompressionLibrary {
 private:
  uint8_t number_of_shuffles_;
  std::string *shuffles_;

 public:
  bool CheckOptions(const Options &options, const bool &compressor);

  bool Compress(char *uncompressed_data, uint64_t uncompressed_size,
                char *compressed_data, uint64_t *compressed_size);

  bool Decompress(char *compressed_data, uint64_t compressed_size,
                  char *decompressed_data, uint64_t *decompressed_size);

  void GetTitle();

  bool GetShuffleInformation(
      std::vector<std::string> *shuffle_information = nullptr,
      uint8_t *minimum_shuffle = nullptr, uint8_t *maximum_shuffle = nullptr);

  std::string GetShuffleName(const uint8_t &shuffle);

  Z3libLibrary();
  ~Z3libLibrary();
};
