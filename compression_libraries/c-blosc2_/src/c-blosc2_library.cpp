/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <blosc2.h>

// SMASH LIBRARIES
#include <c-blosc2_library.hpp>
#include <options.hpp>

bool CBlosc2Library::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  result = CompressionLibrary::CheckNumberThreads("c-blosc2", options, 1, 8);
  if (compressor && result) {
    result = CompressionLibrary::CheckFlags("c-blosc2", options, 0, 2);
    if (result) {
      result =
          CompressionLibrary::CheckCompressionLevel("c-blosc2", options, 0, 9);
    }
  }
  return result;
}

bool CBlosc2Library::SetOptionsCompressor(Options *options) {
  if (initialized_compressor_ || initialized_decompressor_) {
    blosc_destroy();
    initialized_decompressor_ = false;
  }
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) {
    options_ = *options;
    blosc_init();
    blosc_set_compressor("blosclz");
    blosc_set_nthreads(options_.GetNumberThreads());
  }
  return initialized_compressor_;
}

bool CBlosc2Library::SetOptionsDecompressor(Options *options) {
  if (initialized_compressor_ || initialized_decompressor_) {
    blosc_destroy();
    initialized_compressor_ = false;
  }
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) {
    options_ = *options;
    blosc_init();
    blosc_set_nthreads(options_.GetNumberThreads());
  }
  return initialized_decompressor_;
}

void CBlosc2Library::GetCompressedDataSize(char *uncompressed_data,
                                           uint64_t uncompressed_size,
                                           uint64_t *compressed_size) {
  *compressed_size = uncompressed_size + BLOSC_MAX_OVERHEAD;
}

bool CBlosc2Library::Compress(char *uncompressed_data,
                              uint64_t uncompressed_size, char *compressed_data,
                              uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    int csize =
        blosc_compress(options_.GetCompressionLevel(), options_.GetFlags(),
                       sizeof(char), uncompressed_size, uncompressed_data,
                       compressed_data, *compressed_size);
    if (csize == 0 || csize < 0) {
      std::cout << "ERROR: c-blosc2 error when compress data" << std::endl;
      result = false;
    }
    *compressed_size = static_cast<uint64_t>(csize);
  }
  return result;
}

void CBlosc2Library::GetDecompressedDataSize(char *compressed_data,
                                             uint64_t compressed_size,
                                             uint64_t *decompressed_size) {
  int32_t value{0};
  blosc2_cbuffer_sizes(compressed_data, nullptr, &value, nullptr);
  *decompressed_size = value;
}

bool CBlosc2Library::Decompress(char *compressed_data, uint64_t compressed_size,
                                char *decompressed_data,
                                uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    int dsize = blosc_decompress(compressed_data, decompressed_data,
                                 *decompressed_size);
    if (dsize < 0) {
      std::cout << "ERROR: c-blosc2 error when decompress data" << std::endl;
      result = false;
    }
    *decompressed_size = static_cast<uint64_t>(dsize);
  }
  return result;
}

void CBlosc2Library::GetTitle() {
  CompressionLibrary::GetTitle(
      "c-blosc2", "High performance compressor optimized for binary data");
}

bool CBlosc2Library::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 9;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [0-9]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool CBlosc2Library::GetFlagsInformation(
    std::vector<std::string> *flags_information, uint8_t *minimum_flags,
    uint8_t *maximum_flags) {
  if (minimum_flags) *minimum_flags = 0;
  if (maximum_flags) *maximum_flags = 2;
  if (flags_information) {
    flags_information->clear();
    flags_information->push_back("Available values [0-2]");
    flags_information->push_back("0: " + flags_[0]);
    flags_information->push_back("1: " + flags_[1]);
    flags_information->push_back("2: " + flags_[2]);
    flags_information->push_back("[compression]");
  }
  return true;
}

bool CBlosc2Library::GetNumberThreadsInformation(
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

std::string CBlosc2Library::GetFlagsName(const uint8_t &flags) {
  std::string result = "ERROR";
  if (flags < number_of_flags_) {
    result = flags_[flags];
  }
  return result;
}

CBlosc2Library::CBlosc2Library() {
  number_of_flags_ = 3;
  flags_ = new std::string[number_of_flags_];
  flags_[0] = "None";
  flags_[1] = "Byte";
  flags_[2] = "Bit";
}

CBlosc2Library::~CBlosc2Library() {
  if (initialized_compressor_ || initialized_decompressor_) blosc_destroy();
  delete[] flags_;
}
