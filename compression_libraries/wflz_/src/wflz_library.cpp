/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <wfLZ.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <wflz_library.hpp>

bool WflzLibrary::CheckOptions(CpuOptions *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result =
        CpuCompressionLibrary::CheckCompressionLevel("wflz", options, 0, 1);
  }
  return result;
}

void WflzLibrary::GetCompressedDataSize(const char *const uncompressed_data,
                                        const uint64_t &uncompressed_data_size,
                                        uint64_t *compressed_data_size) {
  *compressed_data_size = wfLZ_GetMaxCompressedSize(uncompressed_data_size);
}

bool WflzLibrary::Compress(const char *const uncompressed_data,
                           const uint64_t &uncompressed_data_size,
                           char *compressed_data,
                           uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint8_t *work_mememory = new uint8_t[wfLZ_GetWorkMemSize()];
    uint64_t bytes{0};
    if (options_.GetCompressionLevel() == 0) {
      bytes = wfLZ_Compress(
          reinterpret_cast<const uint8_t *const>(uncompressed_data),
          uncompressed_data_size, reinterpret_cast<uint8_t *>(compressed_data),
          work_mememory, 0);
    } else {
      bytes = wfLZ_CompressFast(
          reinterpret_cast<const uint8_t *const>(uncompressed_data),
          uncompressed_data_size, reinterpret_cast<uint8_t *>(compressed_data),
          work_mememory, 0);
    }
    if (bytes > *compressed_data_size) {
      std::cout << "ERROR: wflz error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_data_size = bytes;
    }
    delete[] work_mememory;
  }
  return result;
}

void WflzLibrary::GetDecompressedDataSize(const char *const compressed_data,
                                          const uint64_t &compressed_data_size,
                                          uint64_t *decompressed_data_size) {
  *decompressed_data_size = wfLZ_GetDecompressedSize(
      reinterpret_cast<const uint8_t *const>(compressed_data));
}

bool WflzLibrary::Decompress(const char *const compressed_data,
                             const uint64_t &compressed_data_size,
                             char *decompressed_data,
                             uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t bytes{0};
    GetDecompressedDataSize(compressed_data, compressed_data_size, &bytes);
    if (bytes <= *decompressed_data_size) {
      wfLZ_Decompress(reinterpret_cast<const uint8_t *const>(compressed_data),
                      reinterpret_cast<uint8_t *>(decompressed_data));
      *decompressed_data_size = bytes;
    } else {
      std::cout << "ERROR: wflz error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void WflzLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle(
      "wflz", "Compression library designed for use in game engines");
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
