/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <lzg.h>
#include <string.h>

// SMASH LIBRARIES
#include <liblzg_library.hpp>
#include <options.hpp>

bool LiblzgLibrary::CheckOptions(const Options &options,
                                 const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel(
        "liblzg", options.GetCompressionLevel(), 1, 9);
  }
  return result;
}

void LiblzgLibrary::GetCompressedDataSize(char *uncompressed_data,
                                          uint64_t uncompressed_size,
                                          uint64_t *compressed_size) {
  *compressed_size = LZG_MaxEncodedSize(uncompressed_size);
}

bool LiblzgLibrary::Compress(char *uncompressed_data,
                             uint64_t uncompressed_size, char *compressed_data,
                             uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    lzg_encoder_config_t config;
    memset(&config, 0, sizeof(config));
    config.level = options_.GetCompressionLevel();
    config.fast = LZG_TRUE;
    uint64_t compressed_bytes = LZG_Encode(
        reinterpret_cast<unsigned char *>(uncompressed_data), uncompressed_size,
        reinterpret_cast<unsigned char *>(compressed_data), *compressed_size,
        &config);
    if (compressed_bytes == 0 || compressed_bytes > *compressed_size) {
      std::cout << "ERROR: liblzg error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_size = compressed_bytes;
    }
  }
  return result;
}

void LiblzgLibrary::GetDecompressedDataSize(char *compressed_data,
                                            uint64_t compressed_size,
                                            uint64_t *decompressed_size) {
  *decompressed_size = LZG_DecodedSize(
      reinterpret_cast<unsigned char *>(compressed_data), compressed_size);
}

bool LiblzgLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                               char *decompressed_data,
                               uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t decompressed_bytes = LZG_Decode(
        reinterpret_cast<unsigned char *>(compressed_data), compressed_size,
        reinterpret_cast<unsigned char *>(decompressed_data),
        *decompressed_size);
    if (decompressed_bytes == 0 || decompressed_bytes > *decompressed_size) {
      std::cout << "ERROR: liblzg error when decompress data" << std::endl;
      result = false;
    } else {
      *decompressed_size = decompressed_bytes;
    }
  }
  return result;
}

void LiblzgLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "liblzg", "Minimal implementation of an LZ77 class compression library");
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
