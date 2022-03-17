/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */
#include <lzham.h>

// SMASH LIBRARIES
#include <lzham_library.hpp>
#include <options.hpp>

bool LzhamLibrary::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  result = CompressionLibrary::CheckWindowSize("lzham", options, 15, 29);
  if (compressor && result) {
    result = CompressionLibrary::CheckCompressionLevel("lzham", options, 0, 4);
    if (result) {
      result = CompressionLibrary::CheckFlags("lzham", options, 0, 7);
    }
  }
  return result;
}

bool LzhamLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                            char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    lzham_compress_params params;
    params.m_struct_size = sizeof(params);
    params.m_dict_size_log2 = options_.GetWindowSize();
    params.m_level =
        static_cast<lzham_compress_level>(options_.GetCompressionLevel());
    params.m_max_helper_threads = -1;
    params.m_num_seed_bytes = 0;
    params.m_pSeed_bytes = NULL;
    params.m_table_update_interval_slow_rate = 0;
    params.m_table_update_rate = 0;
    params.m_table_max_update_interval = 0;
    params.m_compress_flags = flags_values_[options_.GetFlags()];
    params.m_extreme_parsing_max_best_arrivals = 0;
    params.m_fast_bytes = 0;

    lzham_compress_status_t lzham_result = lzham_compress_memory(
        &params, reinterpret_cast<unsigned char *>(compressed_data),
        compressed_size, reinterpret_cast<unsigned char *>(uncompressed_data),
        uncompressed_size, NULL);

    if (lzham_result != LZHAM_COMP_STATUS_SUCCESS) {
      std::cout << "ERROR: lzham error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool LzhamLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                              char *decompressed_data,
                              uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    lzham_decompress_params params;
    params.m_struct_size = sizeof(params);
    params.m_dict_size_log2 = options_.GetWindowSize();
    params.m_table_update_rate = 0;
    params.m_decompress_flags = 0;
    params.m_num_seed_bytes = 0;
    params.m_pSeed_bytes = NULL;
    params.m_table_max_update_interval = 0;
    params.m_table_update_interval_slow_rate = 0;

    lzham_decompress_status_t lzham_result = lzham_decompress_memory(
        &params, reinterpret_cast<unsigned char *>(decompressed_data),
        decompressed_size, reinterpret_cast<unsigned char *>(compressed_data),
        compressed_size, NULL);

    if (lzham_result != LZHAM_DECOMP_STATUS_SUCCESS) {
      std::cout << "ERROR: lzham error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void LzhamLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "lzham", "Lossless data compression codec written in C/C++");
}

bool LzhamLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 4;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [0-4]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool LzhamLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 15;
  if (maximum_size) *maximum_size = 29;
  if (window_size_information) {
    window_size_information->clear();
    window_size_information->push_back("Available values [15-29]");
    window_size_information->push_back("[compression/decompression]");
  }
  return true;
}

bool LzhamLibrary::GetFlagsInformation(
    std::vector<std::string> *flags_information, uint8_t *minimum_flags,
    uint8_t *maximum_flags) {
  if (minimum_flags) *minimum_flags = 0;
  if (maximum_flags) *maximum_flags = 7;
  if (flags_information) {
    flags_information->clear();
    flags_information->push_back("Available values [0-7]");
    flags_information->push_back("0: " + flags_[0]);
    flags_information->push_back("1: " + flags_[1] + " parsing");
    flags_information->push_back("2: " + flags_[2] + " parsing");
    flags_information->push_back("3: " + flags_[3] + " flags");
    flags_information->push_back("4: " + flags_[4] +
                                 " decompression rate for compression ratio");
    flags_information->push_back("5: " + flags_[5] + " flags");
    flags_information->push_back("6: " + flags_[6] + " flags");
    flags_information->push_back("7: " + flags_[7] + " flags");
    flags_information->push_back("[compression]");
  }
  return true;
}

std::string LzhamLibrary::GetFlagsName(const uint8_t &flags) {
  std::string result = "ERROR";
  if (flags < number_of_flags_) {
    result = flags_[flags];
  }
  return result;
}

LzhamLibrary::LzhamLibrary() {
  number_of_flags_ = 8;
  flags_ = new std::string[number_of_flags_];
  flags_values_ = new uint8_t[number_of_flags_];
  flags_[0] = "None";
  flags_values_[0] = 0;
  flags_[1] = "Extreme";
  flags_values_[1] = LZHAM_COMP_FLAG_EXTREME_PARSING;
  flags_[2] = "Deterministic";
  flags_values_[2] = LZHAM_COMP_FLAG_DETERMINISTIC_PARSING;
  flags_[3] = "1 & 2";
  flags_values_[3] = flags_values_[1] + flags_values_[2];
  flags_[4] = "Trade offf";
  flags_values_[4] = LZHAM_COMP_FLAG_TRADEOFF_DECOMPRESSION_RATE_FOR_COMP_RATIO;
  flags_[5] = "1 & 4";
  flags_values_[5] = flags_values_[1] + flags_values_[4];
  flags_[6] = "2 & 4";
  flags_values_[6] = flags_values_[2] + flags_values_[4];
  flags_[7] = "1 & 2 & 4";
  flags_values_[7] = flags_values_[1] + flags_values_[2] + flags_values_[4];
}

LzhamLibrary::~LzhamLibrary() {
  delete[] flags_;
  delete[] flags_values_;
}
