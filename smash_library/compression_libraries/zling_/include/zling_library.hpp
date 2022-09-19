/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#pragma once

#include <libzling.h>

#include <iostream>
#include <string>
#include <vector>
// SMASH LIBRARIES
#include <compression_library.hpp>
#include <options.hpp>

class ZlingReader : public baidu::zling::Inputter  {
 private:
  char *buffer_;
  uint64_t buffer_size_;
  uint64_t total_read_;
  bool error_;

 public:
  size_t GetData(unsigned char* buf, size_t len);
  bool   IsEnd();
  bool   IsErr();
  size_t GetInputSize();
  ZlingReader(char *buffer, const uint64_t &buffer_size);
};

class ZlingWriter : public baidu::zling::Outputter {
 private:
  char *buffer_;
  uint64_t buffer_size_;
  uint64_t total_write_;
  bool error_;

 public:
  size_t PutData(unsigned char* buf, size_t len);
  bool   IsErr();
  size_t GetOutputSize();
  ZlingWriter(char *buffer, const uint64_t &buffer_size);
};

class ZlingLibrary : public CompressionLibrary {
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

  ZlingLibrary();
  ~ZlingLibrary();
};
