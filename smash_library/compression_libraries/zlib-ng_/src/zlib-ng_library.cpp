/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <zlib-ng.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <zlib-ng_library.hpp>

bool ZlibNgLibrary::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result =
        CompressionLibrary::CheckCompressionLevel("zlib-ng", options, 0, 9);
  }
  return result;
}

void ZlibNgLibrary::GetCompressedDataSize(char *uncompressed_data,
                                          uint64_t uncompressed_size,
                                          uint64_t *compressed_size) {
  *compressed_size = zng_compressBound(uncompressed_size);
}

bool ZlibNgLibrary::Compress(char *uncompressed_data,
                             uint64_t uncompressed_size, char *compressed_data,
                             uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    int err = zng_compress2(reinterpret_cast<Bytef *>(compressed_data),
                            compressed_size,
                            reinterpret_cast<Bytef *>(uncompressed_data),
                            uncompressed_size, options_.GetCompressionLevel());
    if (err != Z_OK) {
      std::cout << "ERROR: zlib-ng error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool ZlibNgLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                               char *decompressed_data,
                               uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    int err = zng_uncompress2(
        reinterpret_cast<Bytef *>(decompressed_data), decompressed_size,
        reinterpret_cast<Bytef *>(compressed_data), &compressed_size);
    if (err != Z_OK) {
      std::cout << "ERROR: zlib-ng error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void ZlibNgLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
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
