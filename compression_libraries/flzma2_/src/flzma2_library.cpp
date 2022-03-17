/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <fast-lzma2.h>

// SMASH LIBRARIES
#include <flzma2_library.hpp>
#include <options.hpp>

bool Flzma2Library::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result =
        CompressionLibrary::CheckCompressionLevel("flzma2", options, 1, 10);
    if (result) {
      result = CompressionLibrary::CheckNumberThreads("flzma2", options, 1, 8);
    }
  }
  return result;
}

void Flzma2Library::GetCompressedDataSize(char *uncompressed_data,
                                          uint64_t uncompressed_size,
                                          uint64_t *compressed_size) {
  *compressed_size = FL2_compressBound(uncompressed_size);
}

bool Flzma2Library::Compress(char *uncompressed_data,
                             uint64_t uncompressed_size, char *compressed_data,
                             uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t compressed_bytes = FL2_compressMt(
        compressed_data, *compressed_size, uncompressed_data, uncompressed_size,
        options_.GetCompressionLevel(), options_.GetNumberThreads());
    if (compressed_bytes == 0 || compressed_bytes > *compressed_size) {
      std::cout << "ERROR: flzma2 error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_size = compressed_bytes;
    }
  }
  return result;
}

void Flzma2Library::GetDecompressedDataSize(char *compressed_data,
                                            uint64_t compressed_size,
                                            uint64_t *decompressed_size) {
  *decompressed_size =
      FL2_findDecompressedSize(compressed_data, compressed_size);
}

bool Flzma2Library::Decompress(char *compressed_data, uint64_t compressed_size,
                               char *decompressed_data,
                               uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t decompressed_bytes =
        FL2_decompressMt(decompressed_data, *decompressed_size, compressed_data,
                         compressed_size, options_.GetNumberThreads());
    if (decompressed_bytes == 0 || decompressed_bytes > *decompressed_size) {
      std::cout << "ERROR: flzma2 error when decompress data" << std::endl;
      result = false;
    } else {
      *decompressed_size = decompressed_bytes;
    }
  }
  return result;
}

void Flzma2Library::GetTitle() {
  CompressionLibrary::GetTitle("flzma2",
                               "Lossless high-ratio data compression library "
                               "based on Igor Pavlov's LZMA2 codec from 7-zip");
}

bool Flzma2Library::GetCompressionLevelInformation(
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

bool Flzma2Library::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  if (minimum_threads) *minimum_threads = 1;
  if (maximum_threads) *maximum_threads = 8;
  if (number_threads_information) {
    number_threads_information->clear();
    number_threads_information->push_back("Available values [1-8]");
    number_threads_information->push_back("[compression/decompression]");
  }
  return true;
}

Flzma2Library::Flzma2Library() {}

Flzma2Library::~Flzma2Library() {}
