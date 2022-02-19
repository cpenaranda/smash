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

bool XpackLibrary::CheckOptions(Options options) {
  bool result{true};
  result = CompressionLibrary::CheckCompressionLevel(
      "xpack", options.GetCompressionLevel(), 1, 9);
  return result;
}

bool XpackLibrary::SetOptions(Options options) {
  initialized_ = CheckOptions(options);
  if (initialized_) options_ = options;
  return initialized_;
}

void XpackLibrary::GetCompressedDataSize(uint64_t uncompressed_size,
                                         uint64_t *compressed_size) {
  // There is no way to obtain with Xpack
  *compressed_size = ((uncompressed_size / 5000) + 1) * 5000;
}

bool XpackLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                            char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_};
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

void XpackLibrary::GetDecompressedDataSize(char *compressed_data,
                                           uint64_t compressed_size,
                                           uint64_t *decompressed_size) {
  // There is no way to obtain with Xpack
}

bool XpackLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                              char *decompressed_data,
                              uint64_t *decompressed_size) {
  bool result{initialized_};
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

void XpackLibrary::GetCompressionLevelInformation(
    uint8_t *minimum_level, uint8_t *maximum_level,
    std::vector<std::string> *compression_level_information) {
  if (minimum_level) *minimum_level = 1;
  if (maximum_level) *maximum_level = 9;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [1-9]");
    compression_level_information->push_back("[compression]");
  }
}

void XpackLibrary::GetWindowSizeInformation(
    uint32_t *minimum_size, uint32_t *maximum_size,
    std::vector<std::string> *window_size_information) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
}

void XpackLibrary::GetModeInformation(
    uint8_t *minimum_mode, uint8_t *maximum_mode,
    std::vector<std::string> *mode_information) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
}

void XpackLibrary::GetWorkFactorInformation(
    uint8_t *minimum_factor, uint8_t *maximum_factor,
    std::vector<std::string> *work_factor_information) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
}

void XpackLibrary::GetShuffleInformation(
    uint8_t *minimum_shuffle, uint8_t *maximum_shuffle,
    std::vector<std::string> *shuffle_information) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
}

void XpackLibrary::GetNumberThreadsInformation(
    uint8_t *minimum_threads, uint8_t *maximum_threads,
    std::vector<std::string> *number_threads_information) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
}

void XpackLibrary::GetBackReferenceBitsInformation(
    uint8_t *minimum_bits, uint8_t *maximum_bits,
    std::vector<std::string> *back_reference_information) {
  if (minimum_bits) *minimum_bits = 0;
  if (maximum_bits) *maximum_bits = 0;
  if (back_reference_information) back_reference_information->clear();
}

XpackLibrary::XpackLibrary() {}

XpackLibrary::~XpackLibrary() {}
