/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <lzg.h>
#include <string.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <liblzg_library.hpp>

bool LiblzgLibrary::CheckOptions(CpuOptions *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result =
        CpuCompressionLibrary::CheckCompressionLevel("liblzg", options, 1, 9);
  }
  return result;
}

void LiblzgLibrary::GetCompressedDataSize(
    const char *const uncompressed_data, const uint64_t &uncompressed_data_size,
    uint64_t *compressed_data_size) {
  *compressed_data_size = LZG_MaxEncodedSize(uncompressed_data_size);
}

bool LiblzgLibrary::Compress(const char *const uncompressed_data,
                             const uint64_t &uncompressed_data_size,
                             char *compressed_data,
                             uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    lzg_encoder_config_t config;
    memset(&config, 0, sizeof(config));
    config.level = options_.GetCompressionLevel();
    config.fast = LZG_TRUE;
    uint64_t compressed_bytes = LZG_Encode(
        reinterpret_cast<const unsigned char *const>(uncompressed_data),
        uncompressed_data_size,
        reinterpret_cast<unsigned char *>(compressed_data),
        *compressed_data_size, &config);
    if (compressed_bytes == 0 || compressed_bytes > *compressed_data_size) {
      std::cout << "ERROR: liblzg error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_data_size = compressed_bytes;
    }
  }
  return result;
}

void LiblzgLibrary::GetDecompressedDataSize(
    const char *const compressed_data, const uint64_t &compressed_data_size,
    uint64_t *decompressed_data_size) {
  *decompressed_data_size = LZG_DecodedSize(
      reinterpret_cast<const unsigned char *const>(compressed_data),
      compressed_data_size);
}

bool LiblzgLibrary::Decompress(const char *const compressed_data,
                               const uint64_t &compressed_data_size,
                               char *decompressed_data,
                               uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t decompressed_bytes = LZG_Decode(
        reinterpret_cast<const unsigned char *const>(compressed_data),
        compressed_data_size,
        reinterpret_cast<unsigned char *>(decompressed_data),
        *decompressed_data_size);
    if (decompressed_bytes == 0 ||
        decompressed_bytes > *decompressed_data_size) {
      std::cout << "ERROR: liblzg error when decompress data" << std::endl;
      result = false;
    } else {
      *decompressed_data_size = decompressed_bytes;
    }
  }
  return result;
}

void LiblzgLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle("liblzg",
                                  "Minimal implementation of an LZ77 class "
                                  "compression library (requires no memory)");
}

bool LiblzgLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 1;
  if (maximum_level) *maximum_level = 9;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [1-9]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

LiblzgLibrary::LiblzgLibrary() {}

LiblzgLibrary::~LiblzgLibrary() {}
