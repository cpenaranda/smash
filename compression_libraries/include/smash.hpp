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

class Smash {
 private:
  CompressionLibrary *lib;

 public:
  bool SetOptions(Options options);

  void GetCompressedDataSize(uint64_t uncompressed_size,
                             uint64_t *compressed_size);

  void Compress(char *uncompressed_data, uint64_t uncompressed_size,
                char *compressed_data, uint64_t *compressed_size);

  void GetDecompressedDataSize(char *compressed_data, uint64_t compressed_size,
                               uint64_t *decompressed_size);

  void Decompress(char *compressed_data, uint64_t compressed_size,
                  char *decompressed_data, uint64_t *decompressed_size);

  void GetTitle();

  bool CompareData(char *uncompressed_data, const uint64_t &uncompressed_size,
                   char *decompressed_data, const uint64_t &decompressed_size);

  bool GetCompressionLevelInformation(
      std::vector<std::string> *compression_level_information = nullptr,
      uint8_t *minimum_level = nullptr, uint8_t *maximum_level = nullptr);

  bool GetWindowSizeInformation(
      std::vector<std::string> *window_size_information = nullptr,
      uint32_t *minimum_size = nullptr, uint32_t *maximum_size = nullptr);

  bool GetModeInformation(std::vector<std::string> *mode_information = nullptr,
                          uint8_t *minimum_mode = nullptr,
                          uint8_t *maximum_mode = nullptr);

  bool GetWorkFactorInformation(
      std::vector<std::string> *work_factor_information = nullptr,
      uint8_t *minimum_factor = nullptr, uint8_t *maximum_factor = nullptr);

  bool GetShuffleInformation(
      std::vector<std::string> *shuffle_information = nullptr,
      uint8_t *minimum_shuffle = nullptr, uint8_t *maximum_shuffle = nullptr);

  bool GetNumberThreadsInformation(
      std::vector<std::string> *number_threads_information = nullptr,
      uint8_t *minimum_threads = nullptr, uint8_t *maximum_threads = nullptr);

  bool GetBackReferenceBitsInformation(
      std::vector<std::string> *back_reference_information = nullptr,
      uint8_t *minimum_bits = nullptr, uint8_t *maximum_bits = nullptr);

  std::string GetModeName(const uint8_t &mode);

  std::string GetShuffleName(const uint8_t &shuffle);

  explicit Smash(const std::string &compression_library_name);

  ~Smash();
};
