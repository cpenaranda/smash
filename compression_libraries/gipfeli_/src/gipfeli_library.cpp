/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <gipfeli-internal.h>

// SMASH LIBRARIES
#include <gipfeli_library.hpp>
#include <options.hpp>

bool GipfeliLibrary::CheckOptions(const Options &options,
                                  const bool &compressor) {
  bool result{true};
  return result;
}

bool GipfeliLibrary::SetOptionsCompressor(const Options &options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) {
    options_ = options;
    if (compressor_) {
      delete compressor_;
    }
    compressor_ = new util::compression::gipfeli::Gipfeli();
  }
  return initialized_compressor_;
}

bool GipfeliLibrary::SetOptionsDecompressor(const Options &options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) {
    options_ = options;
    if (compressor_) {
      delete compressor_;
    }
    compressor_ = new util::compression::gipfeli::Gipfeli();
  }
  return initialized_decompressor_;
}

void GipfeliLibrary::GetCompressedDataSize(uint64_t uncompressed_size,
                                           uint64_t *compressed_size) {
  util::compression::Compressor *compressor =
      util::compression::NewGipfeliCompressor();

  *compressed_size = compressor->MaxCompressedLength(uncompressed_size);

  delete compressor;
}

bool GipfeliLibrary::Compress(char *uncompressed_data,
                              uint64_t uncompressed_size, char *compressed_data,
                              uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t real_compressed_size =
        compressor_->RawCompress(uncompressed_data, compressed_data);
    if (real_compressed_size > *compressed_size) {
      std::cout << "ERROR: gipfeli error when compress data" << std::endl;
      result = false;
    }
    *compressed_size = real_compressed_size;
  }
  return result;
}

bool GipfeliLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                                char *decompressed_data,
                                uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    bool gipfeli_result =
        compressor_->RawUncompress(compressed_data, compressed_size,
                                   decompressed_data, *decompressed_size);
    if (!gipfeli_result) {
      std::cout << "ERROR: gipfeli error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void GipfeliLibrary::GetDecompressedDataSize(char *compressed_data,
                                             uint64_t compressed_size,
                                             uint64_t *decompressed_size) {
  util::compression::Compressor *compressor =
      util::compression::NewGipfeliCompressor();

  compressor->GetUncompressedLength(compressed_data, decompressed_size);

  delete compressor;
}

void GipfeliLibrary::GetTitle() {
  CompressionLibrary::GetTitle("gipfeli", "A high-speed compression library");
}

bool GipfeliLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 0;
  if (compression_level_information) compression_level_information->clear();
  return false;
}

bool GipfeliLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool GipfeliLibrary::GetModeInformation(
    std::vector<std::string> *mode_information, uint8_t *minimum_mode,
    uint8_t *maximum_mode, const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
  return false;
}

bool GipfeliLibrary::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool GipfeliLibrary::GetShuffleInformation(
    std::vector<std::string> *shuffle_information, uint8_t *minimum_shuffle,
    uint8_t *maximum_shuffle) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
  return false;
}

bool GipfeliLibrary::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

std::string GipfeliLibrary::GetModeName(const uint8_t &mode) {
  return CompressionLibrary::GetDefaultModeName();
}

std::string GipfeliLibrary::GetShuffleName(const uint8_t &shuffle) {
  return CompressionLibrary::GetDefaultShuffleName();
}

GipfeliLibrary::GipfeliLibrary() { compressor_ = nullptr; }

GipfeliLibrary::~GipfeliLibrary() {
  if (compressor_) delete compressor_;
}
