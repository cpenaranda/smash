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

bool LzhamLibrary::CheckOptions(const Options &options,
                                const bool &compressor) {
  bool result{true};
  result = CompressionLibrary::CheckWindowSize("lzham", options.GetWindowSize(),
                                               15, 29);
  if (compressor && result) {
    result = CompressionLibrary::CheckCompressionLevel(
        "lzham", options.GetCompressionLevel(), 0, 4);
    if (result) {
      result =
          CompressionLibrary::CheckShuffle("lzham", options.GetShuffle(), 0, 7);
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
    params.m_compress_flags = shuffle_values_[options_.GetShuffle()];
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
  CompressionLibrary::GetTitle("lzham", "A lossless data compression codec");
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

bool LzhamLibrary::GetShuffleInformation(
    std::vector<std::string> *shuffle_information, uint8_t *minimum_shuffle,
    uint8_t *maximum_shuffle) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 7;
  if (shuffle_information) {
    shuffle_information->clear();
    shuffle_information->push_back("Available values [0-7]");
    shuffle_information->push_back("0: " + shuffles_[0]);
    shuffle_information->push_back("1: " + shuffles_[1] + " parsing");
    shuffle_information->push_back("2: " + shuffles_[2] + " parsing");
    shuffle_information->push_back("3: " + shuffles_[3] + " flags");
    shuffle_information->push_back("4: " + shuffles_[4] +
                                   " decompression rate for compression ratio");
    shuffle_information->push_back("5: " + shuffles_[5] + " flags");
    shuffle_information->push_back("6: " + shuffles_[6] + " flags");
    shuffle_information->push_back("7: " + shuffles_[7] + " flags");
    shuffle_information->push_back("[compression]");
  }
  return true;
}

std::string LzhamLibrary::GetShuffleName(const uint8_t &shuffle) {
  std::string result = "ERROR";
  if (shuffle < number_of_shuffles_) {
    result = shuffles_[shuffle];
  }
  return result;
}

LzhamLibrary::LzhamLibrary() {
  number_of_shuffles_ = 8;
  shuffles_ = new std::string[number_of_shuffles_];
  shuffle_values_ = new uint8_t[number_of_shuffles_];
  shuffles_[0] = "None";
  shuffle_values_[0] = 0;
  shuffles_[1] = "Extreme";
  shuffle_values_[1] = LZHAM_COMP_FLAG_EXTREME_PARSING;
  shuffles_[2] = "Deterministic";
  shuffle_values_[2] = LZHAM_COMP_FLAG_DETERMINISTIC_PARSING;
  shuffles_[3] = "1 & 2";
  shuffle_values_[3] = shuffle_values_[1] + shuffle_values_[2];
  shuffles_[4] = "Trade offf";
  shuffle_values_[4] =
      LZHAM_COMP_FLAG_TRADEOFF_DECOMPRESSION_RATE_FOR_COMP_RATIO;
  shuffles_[5] = "1 & 4";
  shuffle_values_[5] = shuffle_values_[1] + shuffle_values_[4];
  shuffles_[6] = "2 & 4";
  shuffle_values_[6] = shuffle_values_[2] + shuffle_values_[4];
  shuffles_[7] = "1 & 2 & 4";
  shuffle_values_[7] =
      shuffle_values_[1] + shuffle_values_[2] + shuffle_values_[4];
}

LzhamLibrary::~LzhamLibrary() {
  delete[] shuffles_;
  delete[] shuffle_values_;
}
