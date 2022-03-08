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
// SMASH LIBRARIES
#include <compression_library.hpp>
#include <options.hpp>

class ZpaqReader : public libzpaq::Reader {
 private:
  char *buffer_;
  uint64_t buffer_size_;

 public:
  int get();
  int read(char *buf, int n);
  ZpaqReader(char *buffer, const uint64_t &buffer_size);
};

class ZpaqWriter : public libzpaq::Writer {
 private:
  char *buffer_;
  uint64_t buffer_size_;
  bool error_;

 public:
  void put(int c);
  void write(const char *buf, int n);
  /**
   * @brief Get the final size
   *
   * @param buffer_size Size of the buffer_
   * @return true There is an error. Buffer size is higher than the current
   * buffer_
   * @return false Buffer size is lower than the current buffer_
   */
  bool GetRealSize(uint64_t *buffer_size);
  ZpaqWriter(char *buffer, const uint64_t &buffer_size);
};

class ZpaqLibrary : public CompressionLibrary {
 public:
  bool CheckOptions(Options *options, const bool &compressor);

  bool Compress(char *uncompressed_data, uint64_t uncompressed_size,
                char *compressed_data, uint64_t *compressed_size);

  bool Decompress(char *compressed_data, uint64_t compressed_size,
                  char *decompressed_data, uint64_t *decompressed_size);

  void GetTitle();

  bool GetCompressionLevelInformation(
      std::vector<std::string> *compression_level_information = nullptr,
      uint8_t *minimum_level = nullptr, uint8_t *maximum_level = nullptr);

  ZpaqLibrary();
  ~ZpaqLibrary();
};
