/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <brieflz.h>

// SMASH LIBRARIES
#include <brieflz_library.hpp>
#include <options.hpp>

bool BrieflzLibrary::CheckOptions(const Options &options,
                                  const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel(
        "brieflz", options.GetCompressionLevel(), 1, 10);
  }
  return result;
}

void BrieflzLibrary::GetCompressedDataSize(char *uncompressed_data,
                                           uint64_t uncompressed_size,
                                           uint64_t *compressed_size) {
  *compressed_size = blz_max_packed_size(uncompressed_size);
}

bool BrieflzLibrary::Compress(char *uncompressed_data,
                              uint64_t uncompressed_size, char *compressed_data,
                              uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    char *workmem = new char[blz_workmem_size_level(
        uncompressed_size, options_.GetCompressionLevel())];
    uint64_t final_compression_size{0};
    final_compression_size =
        blz_pack_level(uncompressed_data, compressed_data, uncompressed_size,
                       workmem, options_.GetCompressionLevel());
    if (final_compression_size == BLZ_ERROR ||
        final_compression_size > *compressed_size) {
      std::cout << "ERROR: brieflz error when compress data" << std::endl;
      result = false;
    }
    delete[] workmem;
    *compressed_size = final_compression_size;
  }
  return result;
}

bool BrieflzLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                                char *decompressed_data,
                                uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t final_decompression_size{0};
    final_decompression_size =
        blz_depack_safe(compressed_data, compressed_size, decompressed_data,
                        *decompressed_size);
    if (final_decompression_size != *decompressed_size) {
      std::cout << "ERROR: brieflz error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void BrieflzLibrary::GetTitle() {
  CompressionLibrary::GetTitle("brieflz",
                               "Fast Lempel-Ziv compression library");
}

bool BrieflzLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 1;
  if (maximum_level) *maximum_level = 10;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [1-10]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

BrieflzLibrary::BrieflzLibrary() {}

BrieflzLibrary::~BrieflzLibrary() {}
