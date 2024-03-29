/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <functional>
// Necessary to compile with libbsc
#include <libbsc/libbsc.h>  // NOLINT

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <libbsc_library.hpp>

bool LibbscLibrary::CheckOptions(CpuOptions *options, const bool &compressor) {
  bool result{true};
  result = CpuCompressionLibrary::CheckFlags("libbsc", options, 0, 7);
  if (compressor && result) {
    result =
        CpuCompressionLibrary::CheckCompressionLevel("libbsc", options, 1, 3);
    if (result) {
      result =
          CpuCompressionLibrary::CheckWindowSize("libbsc", options, 10, 28);
      if (result) {
        result =
            CpuCompressionLibrary::CheckBackReference("libbsc", options, 3, 8);
        if (result) {
          result = CpuCompressionLibrary::CheckMode("libbsc", options, 1, 5);
        }
      }
    }
  }
  return result;
}

void LibbscLibrary::GetCompressedDataSize(
    const char *const uncompressed_data, const uint64_t &uncompressed_data_size,
    uint64_t *compressed_data_size) {
  *compressed_data_size = uncompressed_data_size + LIBBSC_HEADER_SIZE;
}

bool LibbscLibrary::Compress(const char *const uncompressed_data,
                             const uint64_t &uncompressed_data_size,
                             char *compressed_data,
                             uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    if (result = (bsc_init(options_.GetFlags()) == LIBBSC_NO_ERROR)) {
      int res = bsc_compress(
          reinterpret_cast<const unsigned char *const>(uncompressed_data),
          reinterpret_cast<unsigned char *>(compressed_data),
          uncompressed_data_size, options_.GetWindowSize(),
          (1 << options_.GetBackReference()) - 1,
          (options_.GetMode() == 1) ? options_.GetMode()
                                    : options_.GetMode() + 1,
          options_.GetCompressionLevel(), options_.GetFlags());
      if (res == LIBBSC_NOT_COMPRESSIBLE || res < LIBBSC_NO_ERROR) {
        result = false;
      }
      *compressed_data_size = res;
    }
  }
  if (!result) {
    std::cout << "ERROR: libbsc error when compress data" << std::endl;
  }
  return result;
}

void LibbscLibrary::GetDecompressedDataSize(
    const char *const compressed_data, const uint64_t &compressed_data_size,
    uint64_t *decompressed_data_size) {
  if (initialized_decompressor_) {
    int decomp_size{0}, comp_size{0};
    int bsc_result = bsc_block_info(
        reinterpret_cast<const unsigned char *const>(compressed_data),
        LIBBSC_HEADER_SIZE, &comp_size, &decomp_size, options_.GetFlags());
    if (bsc_result == LIBBSC_NO_ERROR) {
      *decompressed_data_size = decomp_size;
    }
  }
}

bool LibbscLibrary::Decompress(const char *const compressed_data,
                               const uint64_t &compressed_data_size,
                               char *decompressed_data,
                               uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result = (bsc_init(options_.GetFlags()) == LIBBSC_NO_ERROR)) {
    GetDecompressedDataSize(compressed_data, compressed_data_size,
                            decompressed_data_size);
    int res = bsc_decompress(
        reinterpret_cast<const unsigned char *const>(compressed_data),
        compressed_data_size,
        reinterpret_cast<unsigned char *>(decompressed_data),
        *decompressed_data_size, options_.GetFlags());
    if (res < LIBBSC_NO_ERROR) {
      std::cout << "ERROR: libbsc error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void LibbscLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle(
      "libbsc",
      "High performance file compressor based on lossless, block-sorting data "
      "compression algorithms");
}

bool LibbscLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 1;
  if (maximum_level) *maximum_level = 3;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [1-3]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool LibbscLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 10;
  if (maximum_size) *maximum_size = 28;
  if (window_size_information) {
    window_size_information->clear();
    window_size_information->push_back("Available values [10-28]");
    window_size_information->push_back("[compression]");
  }
  return true;
}

bool LibbscLibrary::GetModeInformation(
    std::vector<std::string> *mode_information, uint8_t *minimum_mode,
    uint8_t *maximum_mode, const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 1;
  if (maximum_mode) *maximum_mode = 5;
  if (mode_information) {
    mode_information->clear();
    mode_information->push_back("Available values [1-5]");
    mode_information->push_back("1: Blocksorter " + modes_[0]);
    mode_information->push_back("2: Blocksorter " + modes_[1]);
    mode_information->push_back("3: Blocksorter " + modes_[2]);
    mode_information->push_back("4: Blocksorter " + modes_[3]);
    mode_information->push_back("5: Blocksorter " + modes_[4]);
    mode_information->push_back("[compression]");
  }
  return true;
}

bool LibbscLibrary::GetFlagsInformation(
    std::vector<std::string> *flags_information, uint8_t *minimum_flags,
    uint8_t *maximum_flags) {
  if (minimum_flags) *minimum_flags = 0;
  if (maximum_flags) *maximum_flags = 7;
  if (flags_information) {
    flags_information->clear();
    flags_information->push_back("Available values [0-7]");
    flags_information->push_back("0: " + flags_[0]);
    flags_information->push_back("1: " + flags_[1]);
    flags_information->push_back("2: " + flags_[2]);
    flags_information->push_back("3: " + flags_[3]);
    flags_information->push_back("4: " + flags_[4]);
    flags_information->push_back("5: " + flags_[5]);
    flags_information->push_back("6: " + flags_[6]);
    flags_information->push_back("7: " + flags_[7]);
    flags_information->push_back("[compression/decompression]");
  }
  return true;
}

bool LibbscLibrary::GetBackReferenceInformation(
    std::vector<std::string> *back_reference_information,
    uint8_t *minimum_back_reference, uint8_t *maximum_back_reference) {
  if (minimum_back_reference) *minimum_back_reference = 3;
  if (maximum_back_reference) *maximum_back_reference = 8;
  if (back_reference_information) {
    back_reference_information->clear();
    back_reference_information->push_back("Available values [3-8]");
    back_reference_information->push_back("[compression]");
  }
  return true;
}

std::string LibbscLibrary::GetModeName(const uint8_t &mode) {
  std::string result = "ERROR";
  if (mode < number_of_modes_) {
    result = modes_[mode - 1];
  }
  return result;
}

std::string LibbscLibrary::GetFlagsName(const uint8_t &flags) {
  std::string result = "ERROR";
  if (flags < number_of_flags_) {
    result = flags_[flags];
  }
  return result;
}

LibbscLibrary::LibbscLibrary() {
  number_of_flags_ = 8;
  number_of_modes_ = 7;
  flags_ = new std::string[number_of_flags_];
  flags_[0] = "None";
  flags_[1] = "Fast Mode";
  flags_[2] = "Paralel";
  flags_[3] = "1 & 2";
  flags_[4] = "Large pages";
  flags_[5] = "1 & 4";
  flags_[6] = "2 & 4";
  flags_[7] = "1 & 2 & 4";

  modes_ = new std::string[number_of_modes_];
  modes_[0] = "Bwt";
  modes_[1] = "St3";
  modes_[2] = "St4";
  modes_[3] = "St5";
  modes_[4] = "St6";
}

LibbscLibrary::~LibbscLibrary() {
  delete[] flags_;
  delete[] modes_;
}
