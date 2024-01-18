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
#include <cstdint>

// CPU-SMASH LIBRARIES
#include <cpu_compression_library.hpp>
#include <cpu_options.hpp>

class CpuSmash {
 private:
  CpuCompressionLibrary *lib;

 public:
  bool SetOptionsCompressor(CpuOptions *options);

  bool SetOptionsDecompressor(CpuOptions *options);

  void GetCompressedDataSize(const char *const uncompressed_data,
                             const uint64_t &uncompressed_data_size,
                             uint64_t *compressed_data_size);

  bool Compress(const char *const uncompressed_data,
                const uint64_t &uncompressed_data_size, char *compressed_data,
                uint64_t *compressed_data_size);

  void GetDecompressedDataSize(const char *const compressed_data,
                               const uint64_t &compressed_data_size,
                               uint64_t *decompressed_data_size);

  bool Decompress(const char *const compressed_data,
                  const uint64_t &compressed_data_size, char *decompressed_data,
                  uint64_t *decompressed_data_size);

  void GetTitle();

  bool CompareData(const char *const uncompressed_data,
                   const uint64_t &uncompressed_data_size,
                   const char *const decompressed_data,
                   const uint64_t &decompressed_data_size);

  bool GetCompressionLevelInformation(
      std::vector<std::string> *compression_level_information = nullptr,
      uint8_t *minimum_level = nullptr, uint8_t *maximum_level = nullptr);

  bool GetWindowSizeInformation(
      std::vector<std::string> *window_size_information = nullptr,
      uint32_t *minimum_size = nullptr, uint32_t *maximum_size = nullptr);

  bool GetModeInformation(std::vector<std::string> *mode_information = nullptr,
                          uint8_t *minimum_mode = nullptr,
                          uint8_t *maximum_mode = nullptr,
                          const uint8_t &compression_level = 0);

  bool GetWorkFactorInformation(
      std::vector<std::string> *work_factor_information = nullptr,
      uint8_t *minimum_factor = nullptr, uint8_t *maximum_factor = nullptr);

  bool GetFlagsInformation(
      std::vector<std::string> *flags_information = nullptr,
      uint8_t *minimum_flags = nullptr, uint8_t *maximum_flags = nullptr);

  bool GetNumberThreadsInformation(
      std::vector<std::string> *number_threads_information = nullptr,
      uint8_t *minimum_threads = nullptr, uint8_t *maximum_threads = nullptr);

  bool GetBackReferenceInformation(
      std::vector<std::string> *back_reference_information = nullptr,
      uint8_t *minimum_back_reference = nullptr,
      uint8_t *maximum_back_reference = nullptr);

  std::string GetModeName(const uint8_t &mode);

  std::string GetFlagsName(const uint8_t &flags);

  CpuOptions GetOptions();

  explicit CpuSmash(const std::string &compression_library_name);

  ~CpuSmash();
};
