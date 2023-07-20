/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <zlib-ng.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <zlib-ng_library.hpp>

bool ZlibNgLibrary::CheckOptions(CpuOptions *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result =
        CpuCompressionLibrary::CheckCompressionLevel("zlib-ng", options, 0, 9);
  }
  return result;
}

void ZlibNgLibrary::GetCompressedDataSize(
    const char *const uncompressed_data, const uint64_t &uncompressed_data_size,
    uint64_t *compressed_data_size) {
  *compressed_data_size = zng_compressBound(uncompressed_data_size);
}

bool ZlibNgLibrary::Compress(const char *const uncompressed_data,
                             const uint64_t &uncompressed_data_size,
                             char *compressed_data,
                             uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    int err = zng_compress2(
        reinterpret_cast<Bytef *>(compressed_data), compressed_data_size,
        reinterpret_cast<const Bytef *const>(uncompressed_data),
        uncompressed_data_size, options_.GetCompressionLevel());
    if (err != Z_OK) {
      std::cout << "ERROR: zlib-ng error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool ZlibNgLibrary::Decompress(const char *const compressed_data,
                               const uint64_t &compressed_data_size,
                               char *decompressed_data,
                               uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t current_compressed_data_size{compressed_data_size};
    int err = zng_uncompress2(
        reinterpret_cast<Bytef *>(decompressed_data), decompressed_data_size,
        reinterpret_cast<const Bytef *const>(compressed_data),
        &current_compressed_data_size);
    if (err != Z_OK) {
      std::cout << "ERROR: zlib-ng error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void ZlibNgLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle(
      "zlib-ng",
      "Zlib data compression library for the next generation systems");
}

bool ZlibNgLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 9;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [0-9]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

ZlibNgLibrary::ZlibNgLibrary() {}

ZlibNgLibrary::~ZlibNgLibrary() {}
