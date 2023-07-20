/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <libdeflate.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <libdeflate_library.hpp>

bool LibdeflateLibrary::CheckOptions(CpuOptions *options,
                                     const bool &compressor) {
  bool result{true};
  result = CpuCompressionLibrary::CheckMode("libdeflate", options, 0, 2);
  if (compressor && result) {
    result = CpuCompressionLibrary::CheckCompressionLevel("libdeflate", options,
                                                          0, 12);
  }
  return result;
}

void LibdeflateLibrary::GetCompressedDataSize(
    const char *const uncompressed_data, const uint64_t &uncompressed_data_size,
    uint64_t *compressed_data_size) {
  switch (options_.GetMode()) {
    case 0:
      // Deflate
      *compressed_data_size =
          libdeflate_deflate_compress_bound(NULL, uncompressed_data_size);
      break;
    case 1:
      // Zlib
      *compressed_data_size =
          libdeflate_zlib_compress_bound(NULL, uncompressed_data_size);
      break;
    case 2:
      // Gzip
      *compressed_data_size =
          libdeflate_gzip_compress_bound(NULL, uncompressed_data_size);
      break;
    default:
      CpuCompressionLibrary::GetCompressedDataSize(
          uncompressed_data, uncompressed_data_size, compressed_data_size);
      break;
  }
}

bool LibdeflateLibrary::Compress(const char *const uncompressed_data,
                                 const uint64_t &uncompressed_data_size,
                                 char *compressed_data,
                                 uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    struct libdeflate_compressor *compressor =
        libdeflate_alloc_compressor(options_.GetCompressionLevel());
    switch (options_.GetMode()) {
      case 0:
        // Deflate
        *compressed_data_size = libdeflate_deflate_compress(
            compressor, uncompressed_data, uncompressed_data_size,
            compressed_data, *compressed_data_size);
        break;
      case 1:
        // Zlib
        *compressed_data_size = libdeflate_zlib_compress(
            compressor, uncompressed_data, uncompressed_data_size,
            compressed_data, *compressed_data_size);
        break;
      case 2:
        // Gzip
        *compressed_data_size = libdeflate_gzip_compress(
            compressor, uncompressed_data, uncompressed_data_size,
            compressed_data, *compressed_data_size);
        break;
      default:
        break;
    }

    libdeflate_free_compressor(compressor);
    if (compressed_data_size == 0) {
      std::cout << "ERROR: libdeflate error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool LibdeflateLibrary::Decompress(const char *const compressed_data,
                                   const uint64_t &compressed_data_size,
                                   char *decompressed_data,
                                   uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    struct libdeflate_decompressor *decompressor =
        libdeflate_alloc_decompressor();
    uint64_t bytes{0};
    libdeflate_result res{LIBDEFLATE_BAD_DATA};
    switch (options_.GetMode()) {
      case 0:
        // Deflate
        res = libdeflate_deflate_decompress(
            decompressor, compressed_data, compressed_data_size,
            decompressed_data, *decompressed_data_size, &bytes);
        break;
      case 1:
        // Zlib
        res = libdeflate_zlib_decompress(
            decompressor, compressed_data, compressed_data_size,
            decompressed_data, *decompressed_data_size, &bytes);
        break;
      case 2:
        // Gzip
        res = libdeflate_gzip_decompress(
            decompressor, compressed_data, compressed_data_size,
            decompressed_data, *decompressed_data_size, &bytes);
        break;
      default:
        break;
    }
    libdeflate_free_decompressor(decompressor);
    *decompressed_data_size = bytes;
    if (res != LIBDEFLATE_SUCCESS) {
      std::cout << "ERROR: libdeflate error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void LibdeflateLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle(
      "libdeflate",
      "Fast, whole-buffer DEFLATE-based compression and decompression");
}

bool LibdeflateLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 12;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [0-12]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool LibdeflateLibrary::GetModeInformation(
    std::vector<std::string> *mode_information, uint8_t *minimum_mode,
    uint8_t *maximum_mode, const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 2;
  if (mode_information) {
    mode_information->clear();
    mode_information->push_back("Available values [0-2]");
    mode_information->push_back("0: " + modes_[0]);
    mode_information->push_back("1: " + modes_[1]);
    mode_information->push_back("2: " + modes_[2]);
    mode_information->push_back("[compression/decompression]");
  }
  return true;
}

std::string LibdeflateLibrary::GetModeName(const uint8_t &mode) {
  std::string result = "ERROR";
  if (mode < number_of_modes_) {
    result = modes_[mode];
  }
  return result;
}

LibdeflateLibrary::LibdeflateLibrary() {
  number_of_modes_ = 3;
  modes_ = new std::string[number_of_modes_];
  modes_[0] = "Deflate";
  modes_[1] = "Zlib";
  modes_[2] = "Gzip";
}

LibdeflateLibrary::~LibdeflateLibrary() { delete[] modes_; }
