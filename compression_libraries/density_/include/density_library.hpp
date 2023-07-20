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

class DensityLibrary : public CpuCompressionLibrary {
 private:
  uint8_t number_of_modes_;
  std::string *modes_;

 public:
  bool CheckOptions(CpuOptions *options, const bool &compressor);

  void GetCompressedDataSize(const char *const uncompressed_data,
                             const uint64_t &uncompressed_data_size,
                             uint64_t *compressed_data_size);

  bool Compress(const char *const uncompressed_data,
                const uint64_t &uncompressed_data_size, char *compressed_data,
                uint64_t *compressed_data_size);

  bool Decompress(const char *const compressed_data,
                  const uint64_t &compressed_data_size, char *decompressed_data,
                  uint64_t *decompressed_data_size);

  void GetTitle();

  bool GetModeInformation(std::vector<std::string> *mode_information = nullptr,
                          uint8_t *minimum_mode = nullptr,
                          uint8_t *maximum_mode = nullptr,
                          const uint8_t &compression_level = 0);

  std::string GetModeName(const uint8_t &mode);

  DensityLibrary();
  ~DensityLibrary();
};
