/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <brieflz.h>

// CPU-SMASH LIBRARIES
#include <brieflz_library.hpp>
#include <cpu_options.hpp>

bool BrieflzLibrary::CheckOptions(CpuOptions *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result =
        CpuCompressionLibrary::CheckCompressionLevel("brieflz", options, 1, 10);
  }
  return result;
}

void BrieflzLibrary::GetCompressedDataSize(
    const char *const uncompressed_data, const uint64_t &uncompressed_data_size,
    uint64_t *compressed_data_size) {
  *compressed_data_size = blz_max_packed_size(uncompressed_data_size);
}

bool BrieflzLibrary::Compress(const char *const uncompressed_data,
                              const uint64_t &uncompressed_data_size,
                              char *compressed_data,
                              uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    char *workmem = new char[blz_workmem_size_level(
        uncompressed_data_size, options_.GetCompressionLevel())];
    uint64_t final_compression_size{0};
    final_compression_size = blz_pack_level(uncompressed_data, compressed_data,
                                            uncompressed_data_size, workmem,
                                            options_.GetCompressionLevel());
    if (final_compression_size == BLZ_ERROR ||
        final_compression_size > *compressed_data_size) {
      std::cout << "ERROR: brieflz error when compress data" << std::endl;
      result = false;
    }
    delete[] workmem;
    *compressed_data_size = final_compression_size;
  }
  return result;
}

bool BrieflzLibrary::Decompress(const char *const compressed_data,
                                const uint64_t &compressed_data_size,
                                char *decompressed_data,
                                uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t final_decompression_size{0};
    final_decompression_size =
        blz_depack_safe(compressed_data, compressed_data_size,
                        decompressed_data, *decompressed_data_size);
    if (final_decompression_size != *decompressed_data_size) {
      std::cout << "ERROR: brieflz error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void BrieflzLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle("brieflz", "Fast LZ77 compression library");
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
