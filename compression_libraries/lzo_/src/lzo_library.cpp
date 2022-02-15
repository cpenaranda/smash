/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <lzo/lzo1.h>
#include <lzo/lzo1a.h>
#include <lzo/lzo1b.h>
#include <lzo/lzo1c.h>
#include <lzo/lzo1f.h>
#include <lzo/lzo1x.h>
#include <lzo/lzo1y.h>
#include <lzo/lzo1z.h>
#include <lzo/lzoconf.h>

// SMASH LIBRARIES
#include <lzo_library.hpp>
#include <options.hpp>

bool LzoLibrary::getFunctions(const uint8_t &mode,
                              const uint8_t &compression_level) {
  bool result{true};
  switch (mode) {
    case 0:
      decompression_work_memory_size_ = LZO1_MEM_DECOMPRESS;
      lzo_decompress_ = lzo1_decompress;
      switch (compression_level) {
        case 0:
          compression_work_memory_size_ = LZO1_MEM_COMPRESS;
          lzo_compress_ = lzo1_compress;
          break;
        case 1:
          compression_work_memory_size_ = LZO1_99_MEM_COMPRESS;
          lzo_compress_ = lzo1_99_compress;
          break;
        default:
          std::cout << "ERROR: Compression level can not be higher than 2 "
                       "using mode value 0 in lzo"
                    << std::endl;
          result = false;
          break;
      }
      break;
    case 1:
      decompression_work_memory_size_ = LZO1A_MEM_DECOMPRESS;
      lzo_decompress_ = lzo1a_decompress;
      switch (compression_level) {
        case 0:
          compression_work_memory_size_ = LZO1A_MEM_COMPRESS;
          lzo_compress_ = lzo1a_compress;
          break;
        case 1:
          compression_work_memory_size_ = LZO1A_99_MEM_COMPRESS;
          lzo_compress_ = lzo1a_99_compress;
          break;
        default:
          std::cout << "ERROR: Compression level can not be higher than 2 "
                       "using mode value 1 in lzo"
                    << std::endl;
          result = false;
          break;
      }
      break;
    case 2:
      decompression_work_memory_size_ = LZO1B_MEM_DECOMPRESS;
      lzo_decompress_ = lzo1b_decompress_safe;
      switch (compression_level) {
        case 0:
          compression_work_memory_size_ = LZO1B_MEM_COMPRESS;
          lzo_compress_ = lzo1b_1_compress;
          break;
        case 1:
          compression_work_memory_size_ = LZO1B_MEM_COMPRESS;
          lzo_compress_ = lzo1b_2_compress;
          break;
        case 2:
          compression_work_memory_size_ = LZO1B_MEM_COMPRESS;
          lzo_compress_ = lzo1b_3_compress;
          break;
        case 3:
          compression_work_memory_size_ = LZO1B_MEM_COMPRESS;
          lzo_compress_ = lzo1b_4_compress;
          break;
        case 4:
          compression_work_memory_size_ = LZO1B_MEM_COMPRESS;
          lzo_compress_ = lzo1b_5_compress;
          break;
        case 5:
          compression_work_memory_size_ = LZO1B_MEM_COMPRESS;
          lzo_compress_ = lzo1b_6_compress;
          break;
        case 6:
          compression_work_memory_size_ = LZO1B_MEM_COMPRESS;
          lzo_compress_ = lzo1b_7_compress;
          break;
        case 7:
          compression_work_memory_size_ = LZO1B_MEM_COMPRESS;
          lzo_compress_ = lzo1b_8_compress;
          break;
        case 8:
          compression_work_memory_size_ = LZO1B_MEM_COMPRESS;
          lzo_compress_ = lzo1b_9_compress;
          break;
        case 9:
          compression_work_memory_size_ = LZO1B_99_MEM_COMPRESS;
          lzo_compress_ = lzo1b_99_compress;
          break;
        case 10:
          compression_work_memory_size_ = LZO1B_999_MEM_COMPRESS;
          lzo_compress_ = lzo1b_999_compress;
          break;
        default:
          std::cout << "ERROR: Compression level can not be higher than 10 "
                       "using mode value 2 in lzo"
                    << std::endl;
          result = false;
          break;
      }
      break;
    case 3:
      decompression_work_memory_size_ = LZO1C_MEM_DECOMPRESS;
      lzo_decompress_ = lzo1c_decompress_safe;
      switch (compression_level) {
        case 0:
          compression_work_memory_size_ = LZO1C_MEM_COMPRESS;
          lzo_compress_ = lzo1c_1_compress;
          break;
        case 1:
          compression_work_memory_size_ = LZO1C_MEM_COMPRESS;
          lzo_compress_ = lzo1c_2_compress;
          break;
        case 2:
          compression_work_memory_size_ = LZO1C_MEM_COMPRESS;
          lzo_compress_ = lzo1c_3_compress;
          break;
        case 3:
          compression_work_memory_size_ = LZO1C_MEM_COMPRESS;
          lzo_compress_ = lzo1c_4_compress;
          break;
        case 4:
          compression_work_memory_size_ = LZO1C_MEM_COMPRESS;
          lzo_compress_ = lzo1c_5_compress;
          break;
        case 5:
          compression_work_memory_size_ = LZO1C_MEM_COMPRESS;
          lzo_compress_ = lzo1c_6_compress;
          break;
        case 6:
          compression_work_memory_size_ = LZO1C_MEM_COMPRESS;
          lzo_compress_ = lzo1c_7_compress;
          break;
        case 7:
          compression_work_memory_size_ = LZO1C_MEM_COMPRESS;
          lzo_compress_ = lzo1c_8_compress;
          break;
        case 8:
          compression_work_memory_size_ = LZO1C_MEM_COMPRESS;
          lzo_compress_ = lzo1c_9_compress;
          break;
        case 9:
          compression_work_memory_size_ = LZO1C_99_MEM_COMPRESS;
          lzo_compress_ = lzo1c_99_compress;
          break;
        case 10:
          compression_work_memory_size_ = LZO1C_999_MEM_COMPRESS;
          lzo_compress_ = lzo1c_999_compress;
          break;
        default:
          std::cout << "ERROR: Compression level can not be higher than 10 "
                       "using mode value 3 in lzo"
                    << std::endl;
          result = false;
          break;
      }
      break;
    case 4:
      decompression_work_memory_size_ = LZO1F_MEM_DECOMPRESS;
      lzo_decompress_ = lzo1f_decompress_safe;
      switch (compression_level) {
        case 0:
          compression_work_memory_size_ = LZO1F_MEM_COMPRESS;
          lzo_compress_ = lzo1f_1_compress;
          break;
        case 1:
          compression_work_memory_size_ = LZO1F_999_MEM_COMPRESS;
          lzo_compress_ = lzo1f_999_compress;
          break;
        default:
          std::cout << "ERROR: Compression level can not be higher than 1 "
                       "using mode value 4 in lzo"
                    << std::endl;
          result = false;
          break;
      }
      break;
    case 5:
      decompression_work_memory_size_ = LZO1X_MEM_DECOMPRESS;
      lzo_decompress_ = lzo1x_decompress_safe;
      switch (compression_level) {
        case 0:
          compression_work_memory_size_ = LZO1X_1_MEM_COMPRESS;
          lzo_compress_ = lzo1x_1_compress;
          break;
        case 1:
          compression_work_memory_size_ = LZO1X_1_11_MEM_COMPRESS;
          lzo_compress_ = lzo1x_1_11_compress;
          break;
        case 2:
          compression_work_memory_size_ = LZO1X_1_12_MEM_COMPRESS;
          lzo_compress_ = lzo1x_1_12_compress;
          break;
        case 3:
          compression_work_memory_size_ = LZO1X_1_15_MEM_COMPRESS;
          lzo_compress_ = lzo1x_1_15_compress;
          break;
        case 4:
          compression_work_memory_size_ = LZO1X_999_MEM_COMPRESS;
          lzo_compress_ = lzo1x_999_compress;
          break;
        default:
          std::cout << "ERROR: Compression level can not be higher than 4 "
                       "using mode value 5 in lzo"
                    << std::endl;
          result = false;
          break;
      }
      break;
    case 6:
      decompression_work_memory_size_ = LZO1Y_MEM_DECOMPRESS;
      lzo_decompress_ = lzo1y_decompress_safe;
      switch (compression_level) {
        case 0:
          compression_work_memory_size_ = LZO1Y_MEM_COMPRESS;
          lzo_compress_ = lzo1y_1_compress;
          break;
        case 1:
          compression_work_memory_size_ = LZO1Y_999_MEM_COMPRESS;
          lzo_compress_ = lzo1y_999_compress;
          break;
        default:
          std::cout << "ERROR: Compression level can not be higher than 1 "
                       "using mode value 6 in lzo"
                    << std::endl;
          result = false;
          break;
      }
      break;
    case 7:
      decompression_work_memory_size_ = LZO1Z_MEM_DECOMPRESS;
      lzo_decompress_ = lzo1z_decompress_safe;
      compression_work_memory_size_ = LZO1Z_999_MEM_COMPRESS;
      lzo_compress_ = lzo1z_999_compress;
      break;
    default:
      std::cout << "ERROR: Mode can not be higher than 7 using lzo"
                << std::endl;
      result = false;
      break;
  }
  return result;
}

void LzoLibrary::getCompressDataSize(uint64_t uncompress_size,
                                     uint64_t *compress_size) {
  *compress_size = ((uncompress_size / 5000) + 1) * 5000;
}

bool LzoLibrary::compress(Options opt, char *uncompress_data,
                          uint64_t uncompress_size, char *compress_data,
                          uint64_t *compress_size) {
  bool result = getFunctions(opt.getMode(), opt.getCompressionLevel());
  if (result) {
    char *work_memory{nullptr};
    int error{0};
    if (compression_work_memory_size_) {
      work_memory = new char[compression_work_memory_size_];
    }
    error = lzo_compress_(reinterpret_cast<unsigned char *>(uncompress_data),
                          uncompress_size,
                          reinterpret_cast<unsigned char *>(compress_data),
                          compress_size, work_memory);
    if (error != LZO_E_OK) {
      std::cout << "ERROR: lzo error when compress data" << std::endl;
      result = false;
    }
    if (work_memory) {
      delete[] work_memory;
    }
  }
  return result;
}

bool LzoLibrary::decompress(char *compress_data, uint64_t compress_size,
                            char *decompress_data, uint64_t *decompress_size) {
  bool result{true};
  char *work_memory{nullptr};
  int error{0};
  if (decompression_work_memory_size_) {
    work_memory = new char[decompression_work_memory_size_];
  }
  error = lzo_decompress_(reinterpret_cast<unsigned char *>(compress_data),
                          compress_size,
                          reinterpret_cast<unsigned char *>(decompress_data),
                          decompress_size, work_memory);
  if (error != LZO_E_OK) {
    result = false;
    std::cout << "ERROR: lzo error when decompress data" << std::endl;
  }
  if (work_memory) {
    delete[] work_memory;
  }
  return result;
}

void LzoLibrary::getTitle() {
  CompressionLibrary::getTitle("lzo", "A real-time data compression library");
}

LzoLibrary::LzoLibrary() {
  compression_work_memory_size_ = 0;
  decompression_work_memory_size_ = 0;
}

LzoLibrary::~LzoLibrary() {}
