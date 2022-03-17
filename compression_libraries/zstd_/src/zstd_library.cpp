/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <zstd.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <zstd_library.hpp>

bool ZstdLibrary::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel("zstd", options, 1, 22);
  }
  return result;
}

void ZstdLibrary::GetCompressedDataSize(char *uncompressed_data,
                                        uint64_t uncompressed_size,
                                        uint64_t *compressed_size) {
  *compressed_size = ZSTD_compressBound(uncompressed_size);
}

bool ZstdLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                           char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t new_size =
        ZSTD_compress(compressed_data, *compressed_size, uncompressed_data,
                      uncompressed_size, options_.GetCompressionLevel());
    if (new_size > *compressed_size) {
      std::cout << "ERROR: zstd error when compress data" << std::endl;
      result = false;
    }
    *compressed_size = new_size;
  }
  return result;
}

bool ZstdLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                             char *decompressed_data,
                             uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t new_size = ZSTD_decompress(decompressed_data, *decompressed_size,
                                        compressed_data, compressed_size);
    if (new_size != *decompressed_size) {
      std::cout << "ERROR: zstd error when decompress data" << std::endl;
      result = false;
    }
    *decompressed_size = new_size;
  }
  return result;
}

void ZstdLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "zstd",
      "Fast lossless compression algorithm, targeting real-time compression "
      "scenarios at zlib-level and better compression ratios");
}

bool ZstdLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 1;
  if (maximum_level) *maximum_level = 22;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [1-22]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

ZstdLibrary::ZstdLibrary() {}

ZstdLibrary::~ZstdLibrary() {}
