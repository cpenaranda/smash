/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#pragma once

#include <libzpaq.h>

#include <iostream>
#include <string>
#include <vector>
// CPU-SMASH LIBRARIES
#include <cpu_compression_library.hpp>
#include <cpu_options.hpp>

class ZpaqReader : public libzpaq::Reader {
 private:
  const char *buffer_;
  uint64_t buffer_size_;

 public:
  int get();
  int read(char *const buf, const int &size);
  ZpaqReader(const char *buffer, const uint64_t &buffer_size);
};

class ZpaqWriter : public libzpaq::Writer {
 private:
  char *buffer_;
  uint64_t buffer_size_;
  bool error_;

 public:
  void put(int c);
  void write(const char *buf, const int &n);
  bool GetRealSize(uint64_t *buffer_size);
  ZpaqWriter(char *buffer, const uint64_t &buffer_size);
};

class ZpaqLibrary : public CpuCompressionLibrary {
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

  ZpaqLibrary();
  ~ZpaqLibrary();
};
