/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <yalz77/lz77.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <yalz77_library.hpp>

bool Yalz77Library::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result =
        CompressionLibrary::CheckCompressionLevel("yalz77", options, 1, 12);
    if (result) {
      result = CompressionLibrary::CheckWindowSize("yalz77", options, 10, 16);
    }
  }
  return result;
}

bool Yalz77Library::Compress(char *uncompressed_data,
                             uint64_t uncompressed_size, char *compressed_data,
                             uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    lz77::compress_t compressor(options_.GetCompressionLevel(),
                                (1 << options_.GetWindowSize()) * 4);
    std::string compressed_result =
        compressor.feed(reinterpret_cast<unsigned char *>(uncompressed_data),
                        reinterpret_cast<unsigned char *>(uncompressed_data +
                                                          uncompressed_size));
    if (compressed_result.size() > *compressed_size) {
      std::cout << "ERROR: yalz77 error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_size = compressed_result.size();
      memcpy(compressed_data, compressed_result.c_str(), *compressed_size);
    }
  }
  return result;
}

bool Yalz77Library::Decompress(char *compressed_data, uint64_t compressed_size,
                               char *decompressed_data,
                               uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    lz77::decompress_t decompressor(*decompressed_size);
    std::string extra;
    bool yalz77_result = decompressor.feed(
        reinterpret_cast<unsigned char *>(compressed_data),
        reinterpret_cast<unsigned char *>(compressed_data + compressed_size),
        extra);
    const std::string &decompressed_result = decompressor.result();
    if (!yalz77_result || !extra.empty() ||
        (decompressed_result.size() > *decompressed_size)) {
      std::cout << "ERROR: yalz77 error when decompress data" << std::endl;
      result = false;
    } else {
      *decompressed_size = decompressed_result.size();
      memcpy(decompressed_data, decompressed_result.c_str(),
             *decompressed_size);
    }
  }
  return result;
}

void Yalz77Library::GetTitle() {
  CompressionLibrary::GetTitle("yalz77",
                               "Variation on the LZ77 compression algorithm");
}

bool Yalz77Library::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 1;
  if (maximum_level) *maximum_level = 12;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [1-12]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool Yalz77Library::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 10;
  if (maximum_size) *maximum_size = 16;
  if (window_size_information) {
    window_size_information->clear();
    window_size_information->push_back("Available values [10-16]");
    window_size_information->push_back("[compression]");
  }
  return true;
}

Yalz77Library::Yalz77Library() {}

Yalz77Library::~Yalz77Library() {}
