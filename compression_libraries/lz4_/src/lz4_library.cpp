/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <lz4/lib/lz4.h>
#include <lz4/lib/lz4hc.h>

// SMASH LIBRARIES
#include <lz4_library.hpp>
#include <options.hpp>

bool Lz4Library::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel("lz4", options, 0, 12);
    if (result) {
      result = CompressionLibrary::CheckMode("lz4", options, 0, 1);
    }
  }
  return result;
}

void Lz4Library::GetCompressedDataSize(char *uncompressed_data,
                                       uint64_t uncompressed_size,
                                       uint64_t *compressed_size) {
  *compressed_size = LZ4_compressBound(uncompressed_size);
}

bool Lz4Library::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                          char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    int bytes_returned{0};
    if (options_.GetMode()) {
      bytes_returned =
          LZ4_compress_HC(uncompressed_data, compressed_data, uncompressed_size,
                          *compressed_size, options_.GetCompressionLevel());
      result = (bytes_returned > 0);
    } else {
      bytes_returned = LZ4_compress_fast(
          uncompressed_data, compressed_data, uncompressed_size,
          *compressed_size,
          1 << static_cast<int>(options_.GetCompressionLevel() * 1.4));
      result = (bytes_returned > 0);
    }
    if (!result) {
      std::cout << "ERROR: lz4 error when compress data" << std::endl;
    }
    *compressed_size = bytes_returned;
  }
  return result;
}

bool Lz4Library::Decompress(char *compressed_data, uint64_t compressed_size,
                            char *decompressed_data,
                            uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    int bytes_returned =
        LZ4_decompress_safe(compressed_data, decompressed_data, compressed_size,
                            *decompressed_size);
    if (bytes_returned < 1) {
      std::cout << "ERROR: lz4 error when decompress data" << std::endl;
      result = false;
    }
    *decompressed_size = bytes_returned;
  }
  return result;
}

void Lz4Library::GetTitle() {
  CompressionLibrary::GetTitle(
      "lz4", "Extremely fast lossless compression library based on LZ77");
}

bool Lz4Library::GetCompressionLevelInformation(
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

bool Lz4Library::GetModeInformation(std::vector<std::string> *mode_information,
                                    uint8_t *minimum_mode,
                                    uint8_t *maximum_mode,
                                    const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 1;
  if (mode_information) {
    mode_information->clear();
    mode_information->push_back("Available values [0-1]");
    mode_information->push_back("0: " + modes_[0]);
    mode_information->push_back("1: " + modes_[1]);
    mode_information->push_back("[compression]");
  }
  return true;
}

std::string Lz4Library::GetModeName(const uint8_t &mode) {
  std::string result = "ERROR";
  if (mode < number_of_modes_) {
    result = modes_[mode];
  }
  return result;
}

Lz4Library::Lz4Library() {
  number_of_modes_ = 2;
  modes_ = new std::string[number_of_modes_];
  modes_[0] = "Fast";
  modes_[1] = "HC";
}

Lz4Library::~Lz4Library() { delete[] modes_; }
