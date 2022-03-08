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

class CBlosc2Library : public CompressionLibrary {
 private:
  uint8_t number_of_flags_;
  std::string *flags_;

 public:
  bool CheckOptions(Options *options, const bool &compressor);

  bool SetOptionsCompressor(Options *options);

  bool SetOptionsDecompressor(Options *options);

  void GetCompressedDataSize(char *uncompressed_data,
                             uint64_t uncompressed_size,
                             uint64_t *compressed_size);

  bool Compress(char *uncompressed_data, uint64_t uncompressed_size,
                char *compressed_data, uint64_t *compressed_size);

  void GetDecompressedDataSize(char *compressed_data, uint64_t compressed_size,
                               uint64_t *decompressed_size);

  bool Decompress(char *compressed_data, uint64_t compressed_size,
                  char *decompressed_data, uint64_t *decompressed_size);

  void GetTitle();

  bool GetCompressionLevelInformation(
      std::vector<std::string> *compression_level_information = nullptr,
      uint8_t *minimum_level = nullptr, uint8_t *maximum_level = nullptr);

  bool GetFlagsInformation(
      std::vector<std::string> *flags_information = nullptr,
      uint8_t *minimum_flags = nullptr, uint8_t *maximum_flags = nullptr);

  bool GetNumberThreadsInformation(
      std::vector<std::string> *number_threads_information = nullptr,
      uint8_t *minimum_threads = nullptr, uint8_t *maximum_threads = nullptr);

  std::string GetFlagsName(const uint8_t &flags);

  CBlosc2Library();
  ~CBlosc2Library();
};
