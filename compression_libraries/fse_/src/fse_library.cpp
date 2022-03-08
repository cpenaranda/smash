/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <fse.h>
#include <huf.h>

// SMASH LIBRARIES
#include <fse_library.hpp>
#include <options.hpp>

bool FseLibrary::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  result = CompressionLibrary::CheckMode("fse", options, 0, 1);
  return result;
}

void FseLibrary::GetCompressedDataSize(char *uncompressed_data,
                                       uint64_t uncompressed_size,
                                       uint64_t *compressed_size) {
  if (initialized_compressor_ || initialized_decompressor_) {
    switch (options_.GetMode()) {
      case 0:
        *compressed_size = FSE_compressBound(uncompressed_size);
        break;
      case 1:
        *compressed_size = HUF_compressBound(uncompressed_size);
        break;
      default:
        break;
    }
  }
}

bool FseLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                          char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t compressed_bytes{0};
    switch (options_.GetMode()) {
      case 0:
        compressed_bytes = FSE_compress(compressed_data, *compressed_size,
                                        uncompressed_data, uncompressed_size);
        break;
      case 1:
        compressed_bytes = HUF_compress(compressed_data, *compressed_size,
                                        uncompressed_data, uncompressed_size);
        break;
      default:
        break;
    }
    if (compressed_bytes == 0 || compressed_bytes > *compressed_size) {
      std::cout << "ERROR: fse error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_size = compressed_bytes;
    }
  }
  return result;
}

bool FseLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                            char *decompressed_data,
                            uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t decompressed_bytes{0};
    switch (options_.GetMode()) {
      case 0:
        decompressed_bytes =
            FSE_decompress(decompressed_data, *decompressed_size,
                           compressed_data, compressed_size);
        break;
      case 1:
        decompressed_bytes =
            HUF_decompress(decompressed_data, *decompressed_size,
                           compressed_data, compressed_size);
        break;
      default:
        break;
    }
    if (decompressed_bytes == 0 || decompressed_bytes > *decompressed_size) {
      std::cout << "ERROR: fse error when decompress data" << std::endl;
      result = false;
    } else {
      *decompressed_size = decompressed_bytes;
    }
  }
  return result;
}

void FseLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "fse",
      "This library proposes two high speed entropy coders: Huff0 & FSE");
}

bool FseLibrary::GetModeInformation(std::vector<std::string> *mode_information,
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
    mode_information->push_back("[compression/decompression]");
  }
  return true;
}

std::string FseLibrary::GetModeName(const uint8_t &mode) {
  std::string result = "ERROR";
  if (mode < number_of_modes_) {
    result = modes_[mode];
  }
  return result;
}

FseLibrary::FseLibrary() {
  number_of_modes_ = 2;
  modes_ = new std::string[number_of_modes_];
  modes_[0] = "FSE";
  modes_[1] = "Huff0";
}

FseLibrary::~FseLibrary() { delete[] modes_; }
