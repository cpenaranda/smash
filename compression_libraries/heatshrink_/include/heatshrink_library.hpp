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

// CPU-SMASH LIBRARIES
#include <cpu_compression_library.hpp>
#include <cpu_options.hpp>

class HeatshrinkLibrary : public CpuCompressionLibrary {
 public:
  bool CheckOptions(CpuOptions *options, const bool &compressor);

  bool Compress(const char *const uncompressed_data,
                const uint64_t &uncompressed_data_size, char *compressed_data,
                uint64_t *compressed_data_size);

  bool Decompress(const char *const compressed_data,
                  const uint64_t &compressed_data_size, char *decompressed_data,
                  uint64_t *decompressed_data_size);

  void GetTitle();

  bool GetWindowSizeInformation(
      std::vector<std::string> *window_size_information = nullptr,
      uint32_t *minimum_size = nullptr, uint32_t *maximum_size = nullptr);

  bool GetBackReferenceInformation(
      std::vector<std::string> *back_reference_information = nullptr,
      uint8_t *minimum_back_reference = nullptr,
      uint8_t *maximum_back_reference = nullptr);

  HeatshrinkLibrary();
  ~HeatshrinkLibrary();
};
