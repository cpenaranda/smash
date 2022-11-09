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

  virtual bool CheckOptions(Options *options, const bool &compressor);

  virtual bool SetOptionsCompressor(Options *options);

  virtual bool SetOptionsDecompressor(Options *options);

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

  virtual bool GetFlagsInformation(
      std::vector<std::string> *flags_information = nullptr,
      uint8_t *minimum_flags = nullptr, uint8_t *maximum_flags = nullptr);

  virtual bool GetNumberThreadsInformation(
      std::vector<std::string> *number_threads_information = nullptr,
      uint8_t *minimum_threads = nullptr, uint8_t *maximum_threads = nullptr);

  virtual bool GetBackReferenceBitsInformation(
      std::vector<std::string> *back_reference_bits_information = nullptr,
      uint8_t *minimum_bits = nullptr, uint8_t *maximum_bits = nullptr);

  virtual std::string GetModeName(const uint8_t &mode);

  virtual std::string GetFlagsName(const uint8_t &flags);

  void GetTitle(const std::string &library_name,
                const std::string &description);

  bool CheckCompressionLevel(const std::string &library_name, Options *options,
                             const uint8_t &minimum_level,
                             const uint8_t &maximum_level);

  bool CheckWindowSize(const std::string &library_name, Options *options,
                       const uint32_t &minimum_size,
                       const uint32_t &maximum_size);

  bool CheckMode(const std::string &library_name, Options *options,
                 const uint8_t &minimum_mode, const uint8_t &maximum_mode);

  bool CheckWorkFactor(const std::string &library_name, Options *options,
                       const uint8_t &minimum_factor,
                       const uint8_t &maximum_factor);

  bool CheckFlags(const std::string &library_name, Options *options,
                  const uint8_t &minimum_flags, const uint8_t &maximum_flags);

  bool CheckNumberThreads(const std::string &library_name, Options *options,
                          const uint8_t &minimum_threads,
                          const uint8_t &maximum_threads);

  bool CheckBackReferenceBits(const std::string &library_name, Options *options,
                              const uint8_t &minimum_bits,
                              const uint8_t &maximum_bits);

  bool CompareData(char *uncompressed_data, const uint64_t &uncompressed_size,
                   char *decompressed_data, const uint64_t &decompressed_size);

  virtual Options GetOptions();

  CompressionLibrary();
  virtual ~CompressionLibrary();
};
