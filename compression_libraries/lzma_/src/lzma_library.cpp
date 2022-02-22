/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <lzma.h>

// SMASH LIBRARIES
#include <lzma_library.hpp>
#include <options.hpp>

bool LzmaLibrary::CheckOptions(const Options &options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckMode("lzma", options.GetMode(), 0, 2);
    if (result) {
      result = CompressionLibrary::CheckNumberThreads(
          "lzma", options.GetNumberThreads(), 1, 8);
    }
  }
  return result;
}

bool LzmaLibrary::SetOptionsCompressor(const Options &options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) options_ = options;
  return initialized_compressor_;
}

bool LzmaLibrary::SetOptionsDecompressor(const Options &options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) options_ = options;
  return initialized_decompressor_;
}

void LzmaLibrary::GetCompressedDataSize(char *uncompressed_data,
                                        uint64_t uncompressed_size,
                                        uint64_t *compressed_size) {
  *compressed_size = lzma_stream_buffer_bound(uncompressed_size);
}

bool LzmaLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                           char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    lzma_stream strm = LZMA_STREAM_INIT;
    lzma_filter filters[2];
    lzma_options_lzma lzma_options;
    lzma_mt config;
    config.flags = 0;
    config.block_size = 0;
    config.timeout = 0;
    config.check = LZMA_CHECK_CRC64;
    config.threads = options_.GetNumberThreads();
    switch (options_.GetMode()) {
      case 0:
        config.preset = LZMA_PRESET_DEFAULT;
        config.filters = nullptr;
        break;
      case 1:
        config.preset = LZMA_PRESET_EXTREME;
        config.filters = nullptr;
        break;
      case 2:
        config.preset = LZMA_PRESET_DEFAULT;
        lzma_lzma_preset(&lzma_options, LZMA_PRESET_DEFAULT);
        filters[1].id = LZMA_VLI_UNKNOWN;
        filters[1].options = nullptr;
        filters[0].id = LZMA_FILTER_LZMA2;
        filters[0].options = &lzma_options;
        config.filters = filters;
        break;
      default:
        break;
    }

    lzma_ret ret_lzma = lzma_stream_encoder_mt(&strm, &config);

    if (ret_lzma != LZMA_OK) {
      result = false;
    } else {
      uint64_t size_aux{0};
      strm.next_in = reinterpret_cast<uint8_t *>(uncompressed_data);
      strm.avail_in = uncompressed_size;
      strm.next_out = reinterpret_cast<uint8_t *>(compressed_data);
      strm.avail_out = *compressed_size;
      ret_lzma = lzma_code(&strm, LZMA_RUN);
      if (ret_lzma != LZMA_OK) {
        result = false;

      } else {
        size_aux = strm.avail_out;
        ret_lzma = lzma_code(&strm, LZMA_FINISH);
        if (ret_lzma != LZMA_STREAM_END) {
          result = false;

        } else {
          *compressed_size =
              (*compressed_size - size_aux) + (size_aux - strm.avail_out);
        }
      }
    }
    lzma_end(&strm);
    if (!result) {
      std::cout << "ERROR: lzma error when compress data" << std::endl;
    }
  }
  return result;
}

void LzmaLibrary::GetDecompressedDataSize(char *compressed_data,
                                          uint64_t compressed_size,
                                          uint64_t *decompressed_size) {
  // There is no way to obtain with Lzma
}

bool LzmaLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                             char *decompressed_data,
                             uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    lzma_stream strm = LZMA_STREAM_INIT;
    lzma_ret ret_lzma = lzma_stream_decoder(
        &strm, UINT64_MAX, LZMA_TELL_UNSUPPORTED_CHECK | LZMA_CONCATENATED);
    if (ret_lzma != LZMA_OK) {
      result = false;
    } else {
      uint64_t size_aux{0};
      strm.next_in = reinterpret_cast<uint8_t *>(compressed_data);
      strm.avail_in = compressed_size;
      strm.next_out = reinterpret_cast<uint8_t *>(decompressed_data);
      strm.avail_out = *decompressed_size;

      ret_lzma = lzma_code(&strm, LZMA_RUN);

      if (ret_lzma != LZMA_OK) {
        result = false;
      } else {
        size_aux = strm.avail_out;
        ret_lzma = lzma_code(&strm, LZMA_FINISH);
        if (ret_lzma != LZMA_STREAM_END) {
          result = false;
        } else {
          *decompressed_size =
              (*decompressed_size - size_aux) + (size_aux - strm.avail_out);
        }
      }
      lzma_end(&strm);
    }
    if (!result) {
      std::cout << "ERROR: lzma error when decompress data" << std::endl;
    }
  }
  return result;
}

void LzmaLibrary::GetTitle() {
  CompressionLibrary::GetTitle("lzma",
                               "A general-purpose data-compression library");
}

bool LzmaLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 0;
  if (compression_level_information) compression_level_information->clear();
  return false;
}

bool LzmaLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool LzmaLibrary::GetModeInformation(std::vector<std::string> *mode_information,
                                     uint8_t *minimum_mode,
                                     uint8_t *maximum_mode,
                                     const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 2;
  if (mode_information) {
    mode_information->clear();
    mode_information->push_back("Available values [0-2]");
    mode_information->push_back("0: " + modes_[0]);
    mode_information->push_back("1: " + modes_[1]);
    mode_information->push_back("2: " + modes_[2]);
    mode_information->push_back("[compression]");
  }
  return true;
}

bool LzmaLibrary::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool LzmaLibrary::GetShuffleInformation(
    std::vector<std::string> *shuffle_information, uint8_t *minimum_shuffle,
    uint8_t *maximum_shuffle) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 0;
  if (shuffle_information) shuffle_information->clear();
  return false;
}

bool LzmaLibrary::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  if (minimum_threads) *minimum_threads = 1;
  if (maximum_threads) *maximum_threads = 8;
  if (number_threads_information) {
    number_threads_information->clear();
    number_threads_information->push_back("Available values [1-8]");
    number_threads_information->push_back("[compression]");
  }
  return true;
}

std::string LzmaLibrary::GetModeName(const uint8_t &mode) {
  std::string result = CompressionLibrary::GetDefaultModeName();
  if (mode < number_of_modes_) {
    result = modes_[mode];
  }
  return result;
}

std::string LzmaLibrary::GetShuffleName(const uint8_t &shuffle) {
  return CompressionLibrary::GetDefaultShuffleName();
}

LzmaLibrary::LzmaLibrary() {
  number_of_modes_ = 3;
  modes_ = new std::string[number_of_modes_];
  modes_[0] = "Default";
  modes_[1] = "Extreme";
  modes_[2] = "Lzma2";
}

LzmaLibrary::~LzmaLibrary() { delete[] modes_; }
