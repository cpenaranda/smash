/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <wfLZ.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <wflz_library.hpp>

bool WflzLibrary::CheckOptions(const Options &options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel(
        "wflz", options.GetCompressionLevel(), 0, 1);
  }
  return result;
}

void WflzLibrary::GetCompressedDataSize(char *uncompressed_data,
                                        uint64_t uncompressed_size,
                                        uint64_t *compressed_size) {
  *compressed_size = wfLZ_GetMaxCompressedSize(uncompressed_size);
}

bool WflzLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                           char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint8_t *work_mememory = new uint8_t[wfLZ_GetWorkMemSize()];
    uint64_t bytes{0};
    if (options_.GetCompressionLevel() == 0) {
      bytes = wfLZ_Compress(
          reinterpret_cast<uint8_t *>(uncompressed_data), uncompressed_size,
          reinterpret_cast<uint8_t *>(compressed_data), work_mememory, 0);
    } else {
      bytes = wfLZ_CompressFast(
          reinterpret_cast<uint8_t *>(uncompressed_data), uncompressed_size,
          reinterpret_cast<uint8_t *>(compressed_data), work_mememory, 0);
    }
    if (bytes > *compressed_size) {
      std::cout << "ERROR: wflz error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_size = bytes;
    }
    delete[] work_mememory;
  }
  return result;
}

void WflzLibrary::GetDecompressedDataSize(char *compressed_data,
                                          uint64_t compressed_size,
                                          uint64_t *decompressed_size) {
  *decompressed_size =
      wfLZ_GetDecompressedSize(reinterpret_cast<uint8_t *>(compressed_data));
}

bool WflzLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                             char *decompressed_data,
                             uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t bytes{0};
    GetDecompressedDataSize(compressed_data, compressed_size, &bytes);
    if (bytes <= *decompressed_size) {
      wfLZ_Decompress(reinterpret_cast<uint8_t *>(compressed_data),
                      reinterpret_cast<uint8_t *>(decompressed_data));
      *decompressed_size = bytes;
    } else {
      std::cout << "ERROR: wflz error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void WflzLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "wflz", "A compression library designed for use in game engines");
}

bool WflzLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 1;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [0-1]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

WflzLibrary::WflzLibrary() {}

WflzLibrary::~WflzLibrary() {}
