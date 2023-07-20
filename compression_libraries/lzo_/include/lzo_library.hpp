/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#pragma once

#include <lzo/lzo1.h>
#include <lzo/lzo1a.h>
#include <lzo/lzo1b.h>
#include <lzo/lzo1c.h>
#include <lzo/lzo1f.h>
#include <lzo/lzo1x.h>
#include <lzo/lzo1y.h>
#include <lzo/lzo1z.h>
#include <lzo/lzoconf.h>

#include <iostream>
#include <string>
#include <vector>

// CPU-SMASH LIBRARIES
#include <cpu_compression_library.hpp>
#include <cpu_options.hpp>
class LzoLibrary : public CpuCompressionLibrary {
 private:
  uint8_t number_of_modes_;
  std::string *modes_;

 private:
  uint64_t compression_work_memory_size_;
  int (*LZO_compress_)(const lzo_bytep, lzo_uint, lzo_bytep, lzo_uintp,
                       lzo_voidp);

  uint64_t decompression_work_memory_size_;
  int (*LZO_decompress_)(const lzo_bytep, lzo_uint, lzo_bytep, lzo_uintp,
                         lzo_voidp);

  void GetFunctions(const uint8_t &mode, const uint8_t &compression_level);

 public:
  bool CheckOptions(CpuOptions *options, const bool &compressor);

  bool SetOptionsCompressor(CpuOptions *options);

  bool SetOptionsDecompressor(CpuOptions *options);

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

  bool GetModeInformation(std::vector<std::string> *mode_information = nullptr,
                          uint8_t *minimum_mode = nullptr,
                          uint8_t *maximum_mode = nullptr,
                          const uint8_t &compression_level = 0);

  std::string GetModeName(const uint8_t &mode);

  LzoLibrary();
  ~LzoLibrary();
};
