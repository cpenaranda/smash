/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <bzlib.h>

// SMASH LIBRARIES
#include <bzip2_library.hpp>
#include <options.hpp>

bool Bzip2Library::CheckOptions(Options options) {
  bool result{true};
  result = CompressionLibrary::CheckCompressionLevel(
      "bzip2", options.GetCompressionLevel(), 1, 9);
  if (result) {
    result = CompressionLibrary::CheckMode("bzip2", options.GetMode(), 0, 1);
    if (result) {
      result = CompressionLibrary::CheckWorkFactor(
          "bzip2", options.GetWorkFactor(), 0, 250);
    }
  }
  return result;
}

bool Bzip2Library::SetOptions(Options options) {
  initialized_ = CheckOptions(options);
  if (initialized_) options_ = options;
  return initialized_;
}

void Bzip2Library::GetCompressedDataSize(uint64_t uncompressed_size,
                                         uint64_t *compressed_size) {
  // There is no way to obtain with Bzip2
  *compressed_size = ((uncompressed_size / 5000) + 1) * 5000;
}

bool Bzip2Library::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                            char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_};
  if (result) {
    int bzerr = BZ2_bzBuffToBuffCompress(
        compressed_data, reinterpret_cast<uint32_t *>(compressed_size),
        uncompressed_data, static_cast<uint32_t>(uncompressed_size),
        options_.GetCompressionLevel(), 0 /* verbosity */,
        options_.GetWorkFactor());
    if (bzerr != BZ_OK && bzerr != BZ_OUTBUFF_FULL) {
      std::cout << "ERROR: bzip2 error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool Bzip2Library::Decompress(char *compressed_data, uint64_t compressed_size,
                              char *decompressed_data,
                              uint64_t *decompressed_size) {
  bool result{initialized_};
  if (result) {
    int bzerr = BZ2_bzBuffToBuffDecompress(
        decompressed_data, reinterpret_cast<uint32_t *>(decompressed_size),
        compressed_data, static_cast<uint32_t>(compressed_size),
        options_.GetMode(), 0 /* verbosity */);
    if (bzerr != BZ_OK) {
      std::cout << "ERROR: bzip2 error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void Bzip2Library::GetDecompressedDataSize(char *compressed_data,
                                           uint64_t compressed_size,
                                           uint64_t *decompressed_size) {
  // There is no way to obtain with Bzip2
}

void Bzip2Library::GetTitle() {
  CompressionLibrary::GetTitle(
      "bzip2", "Based on Burrows-Wheeler algorithm and Huffman coding");
}

void Bzip2Library::GetCompressionLevelInformation(
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

void Bzip2Library::GetWindowSizeInformation(
    uint32_t *minimum_size, uint32_t *maximum_size,
    std::vector<std::string> *window_size_information) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
}

void Bzip2Library::GetModeInformation(
    uint8_t *minimum_mode, uint8_t *maximum_mode,
    std::vector<std::string> *mode_information) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 1;
  if (mode_information) {
    mode_information->clear();
    mode_information->push_back("Available values [0-1]");
    mode_information->push_back("0: Faster decompression using more memory");
    mode_information->push_back("1: Slower decompression using less memory");
    mode_information->push_back("[decompression]");
  }
}

void Bzip2Library::GetWorkFactorInformation(
    uint8_t *minimum_factor, uint8_t *maximum_factor,
    std::vector<std::string> *work_factor_information) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 250;
  if (work_factor_information) {
    work_factor_information->clear();
    work_factor_information->push_back("Available values [0-250]");
    work_factor_information->push_back(
        "Controls the compression behaviour when there is repetitive data");
    work_factor_information->push_back("[compression]");
  }
}

void Bzip2Library::GetShuffleInformation(
    uint8_t *minimum_shuffle, uint8_t *maximum_shuffle,
    std::vector<std::string> *shuffle_information) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
}

void Bzip2Library::GetNumberThreadsInformation(
    uint8_t *minimum_threads, uint8_t *maximum_threads,
    std::vector<std::string> *number_threads_information) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
}

void Bzip2Library::GetBackReferenceBitsInformation(
    uint8_t *minimum_bits, uint8_t *maximum_bits,
    std::vector<std::string> *back_reference_information) {
  if (minimum_bits) *minimum_bits = 0;
  if (maximum_bits) *maximum_bits = 0;
  if (back_reference_information) back_reference_information->clear();
}

Bzip2Library::Bzip2Library() {}

Bzip2Library::~Bzip2Library() {}
