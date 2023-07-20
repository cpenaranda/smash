/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <fse.h>
#include <huf.h>
#include <string.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <fse_library.hpp>

bool FseLibrary::CheckOptions(CpuOptions *options, const bool &compressor) {
  bool result{true};
  result = CpuCompressionLibrary::CheckMode("fse", options, 0, 1);
  return result;
}

void FseLibrary::GetCompressedDataSize(const char *const uncompressed_data,
                                       const uint64_t &uncompressed_data_size,
                                       uint64_t *compressed_data_size) {
  switch (options_.GetMode()) {
    case 0:
      *compressed_data_size =
          FSE_original_compressBound(uncompressed_data_size);
      break;
    case 1: {
      uint64_t current_uncompressed_data_size{uncompressed_data_size};
      *compressed_data_size = 0;
      for (uint32_t bytes = 0; current_uncompressed_data_size;) {
        bytes = (current_uncompressed_data_size < HUF_original_BLOCKSIZE_MAX)
                    ? current_uncompressed_data_size
                    : HUF_original_BLOCKSIZE_MAX;
        *compressed_data_size +=
            HUF_original_compressBound(bytes) + sizeof(bytes);
        current_uncompressed_data_size -= bytes;
      }
      break;
    }
    default:
      CpuCompressionLibrary::GetCompressedDataSize(
          uncompressed_data, uncompressed_data_size, compressed_data_size);
      break;
  }
}

bool FseLibrary::Compress(const char *const uncompressed_data,
                          const uint64_t &uncompressed_data_size,
                          char *compressed_data,
                          uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t compressed_bytes{0};
    switch (options_.GetMode()) {
      case 0:
        compressed_bytes =
            FSE_original_compress(compressed_data, *compressed_data_size,
                                  uncompressed_data, uncompressed_data_size);
        break;
      case 1: {
        uint64_t current_uncompressed_data_size{uncompressed_data_size};
        char *current_uncompressed_data = const_cast<char *>(uncompressed_data);
        for (uint32_t current_bytes_to_compress = 0,
                      current_compressed_bytes = 0;
             current_uncompressed_data_size;) {
          current_bytes_to_compress =
              (current_uncompressed_data_size < HUF_original_BLOCKSIZE_MAX)
                  ? current_uncompressed_data_size
                  : HUF_original_BLOCKSIZE_MAX;
          current_compressed_bytes = HUF_original_compress(
              compressed_data + compressed_bytes +
                  sizeof(current_compressed_bytes),
              *compressed_data_size -
                  (compressed_bytes + sizeof(current_compressed_bytes)),
              current_uncompressed_data, current_bytes_to_compress);
          if (!current_compressed_bytes) {
            // Raw data
            memcpy(compressed_data + compressed_bytes +
                       sizeof(current_compressed_bytes),
                   current_uncompressed_data, current_bytes_to_compress);
            current_compressed_bytes = current_bytes_to_compress;
          }
          *reinterpret_cast<uint32_t *>(compressed_data + compressed_bytes) =
              current_compressed_bytes;
          compressed_bytes +=
              current_compressed_bytes + sizeof(current_compressed_bytes);
          current_uncompressed_data += current_bytes_to_compress;
          current_uncompressed_data_size -= current_bytes_to_compress;
        }
        break;
      }
      default:
        break;
    }
    if (compressed_bytes == 0 || compressed_bytes > *compressed_data_size) {
      std::cout << "ERROR: fse error when compress data" << std::endl;
      result = false;
    } else {
      *compressed_data_size = compressed_bytes;
    }
  }
  return result;
}

bool FseLibrary::Decompress(const char *const compressed_data,
                            const uint64_t &compressed_data_size,
                            char *decompressed_data,
                            uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    uint64_t decompressed_bytes{0};
    switch (options_.GetMode()) {
      case 0:
        decompressed_bytes =
            FSE_original_decompress(decompressed_data, *decompressed_data_size,
                                    compressed_data, compressed_data_size);
        break;
      case 1: {
        uint64_t current_compressed_data_size{compressed_data_size};
        char *current_compressed_data = const_cast<char *>(compressed_data);
        for (uint32_t current_bytes_to_decompress = 0,
                      current_decompressed_bytes = 0;
             current_compressed_data_size;) {
          current_bytes_to_decompress =
              *reinterpret_cast<uint32_t *>(current_compressed_data);
          current_compressed_data += sizeof(current_bytes_to_decompress);
          current_compressed_data_size -= sizeof(current_bytes_to_decompress);
          current_decompressed_bytes =
              (current_bytes_to_decompress == current_compressed_data_size)
                  ? (*decompressed_data_size) - decompressed_bytes
                  : HUF_original_BLOCKSIZE_MAX;
          decompressed_bytes += HUF_original_decompress(
              decompressed_data + decompressed_bytes,
              current_decompressed_bytes, current_compressed_data,
              current_bytes_to_decompress);
          current_compressed_data += current_bytes_to_decompress;
          current_compressed_data_size -= current_bytes_to_decompress;
        }
        break;
      }
      default:
        break;
    }
    if (decompressed_bytes == 0 ||
        decompressed_bytes > *decompressed_data_size) {
      std::cout << "ERROR: fse error when decompress data" << std::endl;
      result = false;
    } else {
      *decompressed_data_size = decompressed_bytes;
    }
  }
  return result;
}

void FseLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle(
      "fse", "Proposes two high speed entropy coders: Huff0 & FSE");
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
