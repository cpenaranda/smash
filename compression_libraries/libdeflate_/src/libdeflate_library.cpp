/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <libdeflate.h>

// SMASH LIBRARIES
#include <libdeflate_library.hpp>
#include <options.hpp>

bool LibdeflateLibrary::CheckOptions(Options options) {
  bool result{true};
  result = CompressionLibrary::CheckCompressionLevel(
      "libdeflate", options.GetCompressionLevel(), 0, 12);
  if (result) {
    result =
        CompressionLibrary::CheckMode("libdeflate", options.GetMode(), 0, 2);
  }
  return result;
}

bool LibdeflateLibrary::SetOptions(Options options) {
  initialized_ = CheckOptions(options);
  if (initialized_) options_ = options;
  return initialized_;
}

void LibdeflateLibrary::GetCompressedDataSize(uint64_t uncompressed_size,
                                              uint64_t *compressed_size) {
  switch (options_.GetMode()) {
    case 0:
      // Deflate
      *compressed_size =
          libdeflate_deflate_compress_bound(NULL, uncompressed_size);
      break;
    case 1:
      // Zlib
      *compressed_size =
          libdeflate_zlib_compress_bound(NULL, uncompressed_size);
      break;
    case 2:
      // Gzip
      *compressed_size =
          libdeflate_gzip_compress_bound(NULL, uncompressed_size);
      break;
    default:
      break;
  }
}

bool LibdeflateLibrary::Compress(char *uncompressed_data,
                                 uint64_t uncompressed_size,
                                 char *compressed_data,
                                 uint64_t *compressed_size) {
  bool result{initialized_};
  if (result) {
    struct libdeflate_compressor *compressor =
        libdeflate_alloc_compressor(options_.GetCompressionLevel());
    switch (options_.GetMode()) {
      case 0:
        // Deflate
        *compressed_size = libdeflate_deflate_compress(
            compressor, uncompressed_data, uncompressed_size, compressed_data,
            *compressed_size);
        break;
      case 1:
        // Zlib
        *compressed_size = libdeflate_zlib_compress(
            compressor, uncompressed_data, uncompressed_size, compressed_data,
            *compressed_size);
        break;
      case 2:
        // Gzip
        *compressed_size = libdeflate_gzip_compress(
            compressor, uncompressed_data, uncompressed_size, compressed_data,
            *compressed_size);
        break;
      default:
        break;
    }

    libdeflate_free_compressor(compressor);
    if (compressed_size == 0) {
      std::cout << "ERROR: libdeflate error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void LibdeflateLibrary::GetDecompressedDataSize(char *compressed_data,
                                                uint64_t compressed_size,
                                                uint64_t *decompressed_size) {
  // There is no way to obtain with Libdeflate
}

bool LibdeflateLibrary::Decompress(char *compress_data, uint64_t compress_size,
                                   char *decompress_data,
                                   uint64_t *decompress_size) {
  bool result{initialized_};
  if (result) {
    struct libdeflate_decompressor *decompressor =
        libdeflate_alloc_decompressor();
    uint64_t bytes{0};
    libdeflate_result res{LIBDEFLATE_BAD_DATA};
    switch (options_.GetMode()) {
      case 0:
        // Deflate
        res = libdeflate_deflate_decompress(decompressor, compress_data,
                                            compress_size, decompress_data,
                                            *decompress_size, &bytes);
        break;
      case 1:
        // Zlib
        res = libdeflate_zlib_decompress(decompressor, compress_data,
                                         compress_size, decompress_data,
                                         *decompress_size, &bytes);
        break;
      case 2:
        // Gzip
        res = libdeflate_gzip_decompress(decompressor, compress_data,
                                         compress_size, decompress_data,
                                         *decompress_size, &bytes);
        break;
      default:
        break;
    }
    libdeflate_free_decompressor(decompressor);
    *decompress_size = bytes;
    if (res != LIBDEFLATE_SUCCESS) {
      std::cout << "ERROR: libdeflate error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void LibdeflateLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "libdeflate",
      "Fast, whole-buffer DEFLATE-based compression and decompression");
}

void LibdeflateLibrary::GetCompressionLevelInformation(
    uint8_t *minimum_level, uint8_t *maximum_level,
    std::vector<std::string> *compression_level_information) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 12;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [0-12]");
    compression_level_information->push_back("[compression]");
  }
}

void LibdeflateLibrary::GetWindowSizeInformation(
    uint32_t *minimum_size, uint32_t *maximum_size,
    std::vector<std::string> *window_size_information) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
}

void LibdeflateLibrary::GetModeInformation(
    uint8_t *minimum_mode, uint8_t *maximum_mode,
    std::vector<std::string> *mode_information) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 2;
  if (mode_information) {
    mode_information->clear();
    mode_information->push_back("Available values [0-2]");
    mode_information->push_back("0: Deflate");
    mode_information->push_back("1: Zlib");
    mode_information->push_back("2: Gzip");
    mode_information->push_back("[compression/decompression]");
  }
}

void LibdeflateLibrary::GetWorkFactorInformation(
    uint8_t *minimum_factor, uint8_t *maximum_factor,
    std::vector<std::string> *work_factor_information) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
}

void LibdeflateLibrary::GetShuffleInformation(
    uint8_t *minimum_shuffle, uint8_t *maximum_shuffle,
    std::vector<std::string> *shuffle_information) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
}

void LibdeflateLibrary::GetNumberThreadsInformation(
    uint8_t *minimum_threads, uint8_t *maximum_threads,
    std::vector<std::string> *number_threads_information) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
}

void LibdeflateLibrary::GetBackReferenceBitsInformation(
    uint8_t *minimum_bits, uint8_t *maximum_bits,
    std::vector<std::string> *back_reference_information) {
  if (minimum_bits) *minimum_bits = 0;
  if (maximum_bits) *maximum_bits = 0;
  if (back_reference_information) back_reference_information->clear();
}

LibdeflateLibrary::LibdeflateLibrary() {}

LibdeflateLibrary::~LibdeflateLibrary() {}
