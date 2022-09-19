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

class Bzip2Library : public CompressionLibrary {
 private:
  uint8_t number_of_modes_;
  std::string *modes_;

 public:
  bool CheckOptions(Options *options, const bool &compressor);

  bool Compress(char *uncompressed_data, uint64_t uncompressed_size,
                char *compressed_data, uint64_t *compressed_size);

  bool Decompress(char *compressed_data, uint64_t compressed_size,
                  char *decompressed_data, uint64_t *decompressed_size);

  void GetTitle();

  bool GetCompressionLevelInformation(
      std::vector<std::string> *compression_level_information = nullptr,
      uint8_t *minimum_level = nullptr, uint8_t *maximum_level = nullptr);

  bool GetModeInformation(std::vector<std::string> *mode_information = nullptr,
                          uint8_t *minimum_mode = nullptr,
                          uint8_t *maximum_mode = nullptr,
                          const uint8_t &compression_level = 0);

  bool GetWorkFactorInformation(
      std::vector<std::string> *work_factor_information = nullptr,
      uint8_t *minimum_factor = nullptr, uint8_t *maximum_factor = nullptr);

  std::string GetModeName(const uint8_t &mode);

  Bzip2Library();
  ~Bzip2Library();
};
