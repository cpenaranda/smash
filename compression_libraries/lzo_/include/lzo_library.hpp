/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#pragma once

#include <lzo1.h>
#include <lzo1a.h>
#include <lzo1b.h>
#include <lzo1c.h>
#include <lzo1f.h>
#include <lzo1x.h>
#include <lzo1y.h>
#include <lzo1z.h>
#include <lzoconf.h>

#include <iostream>
#include <string>
#include <vector>

// SMASH LIBRARIES
#include <compression_library.hpp>
#include <options.hpp>
class LzoLibrary : public CompressionLibrary {
 private:
  uint64_t compression_work_memory_size_;
  int (*LZO_compress_)(const lzo_bytep, lzo_uint, lzo_bytep, lzo_uintp,
                       lzo_voidp);

  uint64_t decompression_work_memory_size_;
  int (*LZO_decompress_)(const lzo_bytep, lzo_uint, lzo_bytep, lzo_uintp,
                         lzo_voidp);

  void GetFunctions(const uint8_t &mode, const uint8_t &compression_level);

 public:
  bool CheckOptions(Options options);

  bool SetOptions(Options options);

  void GetCompressedDataSize(uint64_t uncompressed_size,
                             uint64_t *compressed_size);

  bool Compress(char *uncompressed_data, uint64_t uncompressed_size,
                char *compressed_data, uint64_t *compressed_size);

  void GetDecompressedDataSize(char *compressed_data, uint64_t compressed_size,
                               uint64_t *decompressed_size);

  bool Decompress(char *compressed_data, uint64_t compressed_size,
                  char *decompressed_data, uint64_t *decompressed_size);

  void GetTitle();

  void GetCompressionLevelInformation(
      uint8_t *minimum_level, uint8_t *maximum_level,
      std::vector<std::string> *compression_level_information);

  void GetWindowSizeInformation(
      uint32_t *minimum_size, uint32_t *maximum_size,
      std::vector<std::string> *window_size_information);

  void GetModeInformation(uint8_t *minimum_mode, uint8_t *maximum_mode,
                          std::vector<std::string> *mode_information);

  void GetWorkFactorInformation(
      uint8_t *minimum_factor, uint8_t *maximum_factor,
      std::vector<std::string> *work_factor_information);

  void GetShuffleInformation(uint8_t *minimum_shuffle, uint8_t *maximum_shuffle,
                             std::vector<std::string> *shuffle_information);

  void GetNumberThreadsInformation(
      uint8_t *minimum_threads, uint8_t *maximum_threads,
      std::vector<std::string> *number_threads_information);

  void GetBackReferenceBitsInformation(
      uint8_t *minimum_bits, uint8_t *maximum_bits,
      std::vector<std::string> *back_reference_information);

  LzoLibrary();
  ~LzoLibrary();
};
