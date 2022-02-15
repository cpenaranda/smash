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
// SMASH LIBRARIES
#include <compression_library.hpp>
#include <options.hpp>
class LzoLibrary : public CompressionLibrary {
 private:
  uint64_t compression_work_memory_size_;
  int (*lzo_compress_)(const lzo_bytep, lzo_uint, lzo_bytep, lzo_uintp,
                       lzo_voidp);

  uint64_t decompression_work_memory_size_;
  int (*lzo_decompress_)(const lzo_bytep, lzo_uint, lzo_bytep, lzo_uintp,
                         lzo_voidp);

  bool getFunctions(const uint8_t &mode, const uint8_t &compression_level);

 public:
  void getCompressDataSize(uint64_t uncompress_size, uint64_t *compress_size);

  bool compress(Options opt, char *uncompress_data, uint64_t uncompress_size,
                char *compress_data, uint64_t *compress_size);

  bool decompress(char *compress_data, uint64_t compress_size,
                  char *decompress_data, uint64_t *decompress_size);

  void getTitle();

  LzoLibrary();
  ~LzoLibrary();
};
