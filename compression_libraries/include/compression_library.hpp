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
#include <options.hpp>

class CompressionLibrary {
 public:
  Options options_;
  bool initialized_;

  virtual bool CheckOptions(Options options) = 0;

  virtual bool SetOptions(Options options) = 0;

  virtual void GetCompressedDataSize(uint64_t uncompressed_size,
                                     uint64_t *compressed_size) = 0;

  virtual bool Compress(char *uncompressed_data, uint64_t uncompressed_size,
                        char *compressed_data, uint64_t *compressed_size) = 0;

  virtual void GetDecompressedDataSize(char *compressed_data,
                                       uint64_t compressed_size,
                                       uint64_t *decompressed_size) = 0;

  virtual bool Decompress(char *compressed_data, uint64_t compressed_size,
                          char *decompressed_data,
                          uint64_t *decompressed_size) = 0;

  virtual void GetTitle() = 0;

  virtual bool GetCompressionLevelInformation(
      std::vector<std::string> *compression_level_information = nullptr,
      uint8_t *minimum_level = nullptr, uint8_t *maximum_level = nullptr) = 0;

  virtual bool GetWindowSizeInformation(
      std::vector<std::string> *window_size_information = nullptr,
      uint32_t *minimum_size = nullptr, uint32_t *maximum_size = nullptr) = 0;

  virtual bool GetModeInformation(
      std::vector<std::string> *mode_information = nullptr,
      uint8_t *minimum_mode = nullptr, uint8_t *maximum_mode = nullptr) = 0;

  virtual bool GetWorkFactorInformation(
      std::vector<std::string> *work_factor_information = nullptr,
      uint8_t *minimum_factor = nullptr, uint8_t *maximum_factor = nullptr) = 0;

  virtual bool GetShuffleInformation(
      std::vector<std::string> *shuffle_information = nullptr,
      uint8_t *minimum_shuffle = nullptr,
      uint8_t *maximum_shuffle = nullptr) = 0;

  virtual bool GetNumberThreadsInformation(
      std::vector<std::string> *number_threads_information = nullptr,
      uint8_t *minimum_threads = nullptr,
      uint8_t *maximum_threads = nullptr) = 0;

  virtual bool GetBackReferenceBitsInformation(
      std::vector<std::string> *back_reference_information = nullptr,
      uint8_t *minimum_bits = nullptr, uint8_t *maximum_bits = nullptr) = 0;

  virtual std::string GetModeName(const uint8_t &mode) = 0;

  virtual std::string GetShuffleName(const uint8_t &shuffle) = 0;

  void GetTitle(const std::string &library_name,
                const std::string &description);

  bool CheckCompressionLevel(std::string library_name, uint8_t level,
                             uint8_t minimum_level, uint8_t maximum_level);

  bool CheckWindowSize(std::string library_name, uint32_t window_size,
                       uint32_t minimum_size, uint32_t maximum_size);

  bool CheckMode(std::string library_name, uint8_t mode, uint8_t minimum_mode,
                 uint8_t maximum_mode);

  bool CheckWorkFactor(std::string library_name, uint8_t work_factor,
                       uint8_t minimum_factor, uint8_t maximum_factor);

  bool CheckShuffle(std::string library_name, uint8_t shuffle,
                    uint8_t minimum_shuffle, uint8_t maximum_shuffle);

  bool CheckNumberThreads(std::string library_name, uint8_t number_threads,
                          uint8_t minimum_threads, uint8_t maximum_threads);

  bool CheckBackReferenceBits(std::string library_name,
                              uint8_t back_reference_bits, uint8_t minimum_bits,
                              uint8_t maximum_bits);

  bool CompareData(char *uncompressed_data, const uint64_t &uncompressed_size,
                   char *decompressed_data, const uint64_t &decompressed_size);

  std::string GetDefaultModeName();

  std::string GetDefaultShuffleName();

  CompressionLibrary();
  virtual ~CompressionLibrary();
};
