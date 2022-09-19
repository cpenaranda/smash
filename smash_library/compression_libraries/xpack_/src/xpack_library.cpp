/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <libxpack.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <xpack_library.hpp>

bool XpackLibrary::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel("xpack", options, 1, 9);
  }
  return result;
}

bool XpackLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                            char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    xpack_compressor *compressor = xpack_alloc_compressor(
        uncompressed_size, options_.GetCompressionLevel());
    *compressed_size =
        xpack_compress(compressor, uncompressed_data, uncompressed_size,
                       compressed_data, *compressed_size);
    if (!*compressed_size) {
      std::cout << "ERROR: xpack error when compress data" << std::endl;
      result = false;
    }
    xpack_free_compressor(compressor);
  }
  return result;
}

bool XpackLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                              char *decompressed_data,
                              uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    xpack_decompressor *decompressor = xpack_alloc_decompressor();
    uint64_t uncompressed_size{0};
    decompress_result error = xpack_decompress(
        decompressor, compressed_data, compressed_size, decompressed_data,
        *decompressed_size, &uncompressed_size);
    if (error != DECOMPRESS_SUCCESS ||
        uncompressed_size != *decompressed_size) {
      std::cout << "ERROR: xpack error when decompress data" << std::endl;
      result = false;
    }
    xpack_free_decompressor(decompressor);
  }
  return result;
}

void XpackLibrary::GetTitle() {
  CompressionLibrary::GetTitle("xpack",
                               "Has been inspired by the DEFLATE, LZX, and "
                               "Zstandard formats, among others");
}

bool XpackLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 1;
  if (maximum_level) *maximum_level = 9;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [1-9]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

XpackLibrary::XpackLibrary() {}

XpackLibrary::~XpackLibrary() {}
