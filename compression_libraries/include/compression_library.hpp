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
  bool initialized_compressor_;
  bool initialized_decompressor_;

  virtual bool CheckOptions(const Options &options, const bool &compressor);

  virtual bool SetOptionsCompressor(const Options &options);

  virtual bool SetOptionsDecompressor(const Options &options);

  virtual void GetCompressedDataSize(char *uncompressed_data,
                                     uint64_t uncompressed_size,
                                     uint64_t *compressed_size);

  virtual bool Compress(char *uncompressed_data, uint64_t uncompressed_size,
                        char *compressed_data, uint64_t *compressed_size) = 0;

  virtual void GetDecompressedDataSize(char *compressed_data,
                                       uint64_t compressed_size,
                                       uint64_t *decompressed_size);

  virtual bool Decompress(char *compressed_data, uint64_t compressed_size,
                          char *decompressed_data,
                          uint64_t *decompressed_size) = 0;

  virtual void GetTitle() = 0;

  virtual bool GetCompressionLevelInformation(
      std::vector<std::string> *compression_level_information = nullptr,
      uint8_t *minimum_level = nullptr, uint8_t *maximum_level = nullptr);

  virtual bool GetWindowSizeInformation(
      std::vector<std::string> *window_size_information = nullptr,
      uint32_t *minimum_size = nullptr, uint32_t *maximum_size = nullptr);

  virtual bool GetModeInformation(
      std::vector<std::string> *mode_information = nullptr,
      uint8_t *minimum_mode = nullptr, uint8_t *maximum_mode = nullptr,
      const uint8_t &compression_level = 0);

  virtual bool GetWorkFactorInformation(
      std::vector<std::string> *work_factor_information = nullptr,
      uint8_t *minimum_factor = nullptr, uint8_t *maximum_factor = nullptr);

  virtual bool GetShuffleInformation(
      std::vector<std::string> *shuffle_information = nullptr,
      uint8_t *minimum_shuffle = nullptr,
      uint8_t *maximum_shuffle = nullptr);

  virtual bool GetNumberThreadsInformation(
      std::vector<std::string> *number_threads_information = nullptr,
      uint8_t *minimum_threads = nullptr,
      uint8_t *maximum_threads = nullptr);

  virtual std::string GetModeName(const uint8_t &mode);

  virtual std::string GetShuffleName(const uint8_t &shuffle);

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

  bool CompareData(char *uncompressed_data, const uint64_t &uncompressed_size,
                   char *decompressed_data, const uint64_t &decompressed_size);

  CompressionLibrary();
  virtual ~CompressionLibrary();
};
