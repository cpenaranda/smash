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
#include <cpu_options.hpp>

class CpuCompressionLibrary {
 public:
  CpuOptions options_;
  bool initialized_compressor_;
  bool initialized_decompressor_;

  virtual bool CheckOptions(CpuOptions *options, const bool &compressor);

  virtual bool SetOptionsCompressor(CpuOptions *options);

  virtual bool SetOptionsDecompressor(CpuOptions *options);

  virtual void GetCompressedDataSize(const char *const uncompressed_data,
                                     const uint64_t &uncompressed_data_size,
                                     uint64_t *compressed_data_size);

  virtual void GetDecompressedDataSize(const char *const compressed_data,
                                       const uint64_t &compressed_data_size,
                                       uint64_t *decompressed_data_size);

  virtual bool Compress(const char *const uncompressed_data,
                        const uint64_t &uncompressed_data_size,
                        char *compressed_data,
                        uint64_t *compressed_data_size) = 0;

  virtual bool Decompress(const char *const compressed_data,
                          const uint64_t &compressed_data_size,
                          char *decompressed_data,
                          uint64_t *decompressed_data_size) = 0;

  virtual void GetTitle() = 0;

  void GetTitle(const std::string &library_name,
                const std::string &description);

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

  virtual bool GetBackReferenceInformation(
      std::vector<std::string> *back_reference_information = nullptr,
      uint8_t *minimum_back_reference = nullptr,
      uint8_t *maximum_back_reference = nullptr);

  virtual std::string GetModeName(const uint8_t &mode);

  virtual std::string GetFlagsName(const uint8_t &flags);

  bool CompareData(const char *const uncompressed_data,
                   const uint64_t &uncompressed_data_size,
                   const char *const decompressed_data,
                   const uint64_t &decompressed_data_size);

  bool CheckCompressionLevel(const std::string &library_name,
                             CpuOptions *options, const uint8_t &minimum_level,
                             const uint8_t &maximum_level);

  bool CheckWindowSize(const std::string &library_name, CpuOptions *options,
                       const uint32_t &minimum_size,
                       const uint32_t &maximum_size);

  bool CheckMode(const std::string &library_name, CpuOptions *options,
                 const uint8_t &minimum_mode, const uint8_t &maximum_mode);

  bool CheckWorkFactor(const std::string &library_name, CpuOptions *options,
                       const uint8_t &minimum_factor,
                       const uint8_t &maximum_factor);

  bool CheckFlags(const std::string &library_name, CpuOptions *options,
                  const uint8_t &minimum_flags, const uint8_t &maximum_flags);

  bool CheckNumberThreads(const std::string &library_name, CpuOptions *options,
                          const uint8_t &minimum_threads,
                          const uint8_t &maximum_threads);

  bool CheckBackReference(const std::string &library_name, CpuOptions *options,
                          const uint8_t &minimum_back_reference,
                          const uint8_t &maximum_back_reference);

  virtual CpuOptions GetOptions();

  CpuCompressionLibrary();

  virtual ~CpuCompressionLibrary();
};
