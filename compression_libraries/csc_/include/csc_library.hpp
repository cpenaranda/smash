/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#pragma once

#include <Types.h>

#include <iostream>
#include <string>
#include <vector>

// CPU-SMASH LIBRARIES
#include <cpu_compression_library.hpp>
#include <cpu_options.hpp>

class CscReader : ISeqInStream {
 private:
  const char *buffer_;
  uint64_t buffer_size_;
  uint64_t total_read_;

 public:
  static SRes RealRead(void *istream, void *const buf, size_t *size);
  size_t GetData(void *const buf, const size_t &len);
  size_t GetInputSize();
  CscReader(const char *buffer, const uint64_t &buffer_size);
};

class CscWriter : ISeqOutStream {
 private:
  char *buffer_;
  uint64_t buffer_size_;
  uint64_t total_write_;

 public:
  static size_t RealWrite(void *ostream, const void *buf, size_t size);
  size_t PutData(const void *buf, const size_t &len);
  size_t GetOutputSize();
  CscWriter(char *buffer, uint64_t buffer_size);
};

class CscLibrary : public CpuCompressionLibrary {
 private:
  uint8_t number_of_flags_;
  std::string *flags_;

 public:
  bool CheckOptions(CpuOptions *options, const bool &compressor);

  bool Compress(const char *const uncompressed_data,
                const uint64_t &uncompressed_data_size, char *compressed_data,
                uint64_t *compressed_data_size);

  bool Decompress(const char *const compressed_data,
                  const uint64_t &compressed_data_size, char *decompressed_data,
                  uint64_t *decompressed_data_size);

  void GetTitle();

  bool GetCompressionLevelInformation(
      std::vector<std::string> *compression_level_information = nullptr,
      uint8_t *minimum_level = nullptr, uint8_t *maximum_level = nullptr);

  bool GetFlagsInformation(
      std::vector<std::string> *flags_information = nullptr,
      uint8_t *minimum_flags = nullptr, uint8_t *maximum_flags = nullptr);

  bool GetWindowSizeInformation(
      std::vector<std::string> *window_size_information = nullptr,
      uint32_t *minimum_size = nullptr, uint32_t *maximum_size = nullptr);

  std::string GetFlagsName(const uint8_t &flags);

  CscLibrary();
  ~CscLibrary();
};
