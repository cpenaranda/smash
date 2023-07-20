/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <miniz.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <miniz_library.hpp>

bool MinizLibrary::CheckOptions(CpuOptions *options, const bool &compressor) {
  bool result{true};
  result = CpuCompressionLibrary::CheckWindowSize("miniz", options, 10, 11);
  if (compressor && result) {
    result =
        CpuCompressionLibrary::CheckCompressionLevel("miniz", options, 1, 9);
    if (result) {
      result = CpuCompressionLibrary::CheckMode("miniz", options, 0, 4);
    }
  }
  return result;
}

void MinizLibrary::GetCompressedDataSize(const char *const uncompressed_data,
                                         const uint64_t &uncompressed_data_size,
                                         uint64_t *compressed_data_size) {
  *compressed_data_size = mz_compressBound(uncompressed_data_size);
}

bool MinizLibrary::Compress(const char *const uncompressed_data,
                            const uint64_t &uncompressed_data_size,
                            char *compressed_data,
                            uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    mz_stream stream;
    memset(&stream, 0, sizeof(stream));
    stream.next_in =
        reinterpret_cast<const unsigned char *const>(uncompressed_data);
    stream.avail_in = uncompressed_data_size;
    stream.next_out = reinterpret_cast<unsigned char *>(compressed_data);
    stream.avail_out = *compressed_data_size;
    int miniz_result = mz_deflateInit2(
        &stream, options_.GetCompressionLevel(), MZ_DEFLATED,
        options_.GetWindowSize() == 10 ? MZ_DEFAULT_WINDOW_BITS
                                       : -MZ_DEFAULT_WINDOW_BITS,
        1 /* the param is ignored*/, options_.GetMode());
    if (miniz_result != MZ_OK) {
      result = false;
    } else {
      miniz_result = mz_deflate(&stream, MZ_FINISH);
      if ((miniz_result != MZ_OK && miniz_result != MZ_STREAM_END) ||
          stream.avail_in) {
        result = false;
      } else {
        miniz_result = mz_deflateEnd(&stream);
        if (miniz_result != MZ_OK) {
          result = false;
        }
        *compressed_data_size = stream.total_out;
      }
    }
    if (!result) {
      std::cout << "ERROR: miniz error when compress data" << std::endl;
    }
  }
  return result;
}

bool MinizLibrary::Decompress(const char *const compressed_data,
                              const uint64_t &compressed_data_size,
                              char *decompressed_data,
                              uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    mz_stream stream;
    memset(&stream, 0, sizeof(stream));
    stream.next_in =
        reinterpret_cast<const unsigned char *const>(compressed_data);
    stream.avail_in = compressed_data_size;
    stream.next_out = reinterpret_cast<unsigned char *>(decompressed_data);
    stream.avail_out = *decompressed_data_size;
    int miniz_result = mz_inflateInit2(&stream, options_.GetWindowSize() == 10
                                                    ? MZ_DEFAULT_WINDOW_BITS
                                                    : -MZ_DEFAULT_WINDOW_BITS);
    if (miniz_result != MZ_OK) {
      result = false;
    } else {
      miniz_result = mz_inflate(&stream, MZ_FINISH);
      if ((miniz_result != MZ_OK && miniz_result != MZ_STREAM_END) ||
          stream.avail_in) {
        result = false;
      } else {
        miniz_result = mz_inflateEnd(&stream);
        if (miniz_result != MZ_OK) {
          result = false;
        }
        *decompressed_data_size = stream.total_out;
      }
    }
    if (!result) {
      std::cout << "ERROR: miniz error when decompress data" << std::endl;
    }
  }
  return result;
}

void MinizLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle(
      "miniz", "Lossless, high performance data compression library");
}

bool MinizLibrary::GetCompressionLevelInformation(
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

bool MinizLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 10;
  if (maximum_size) *maximum_size = 11;
  if (window_size_information) {
    window_size_information->clear();
    window_size_information->push_back("Available values [10-11]");
    window_size_information->push_back("[compression/decompression]");
  }
  return true;
}

bool MinizLibrary::GetModeInformation(
    std::vector<std::string> *mode_information, uint8_t *minimum_mode,
    uint8_t *maximum_mode, const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 4;
  if (mode_information) {
    mode_information->clear();
    mode_information->push_back("Available values [0-4]");
    mode_information->push_back("0: " + modes_[0]);
    mode_information->push_back("1: " + modes_[1]);
    mode_information->push_back("2: " + modes_[2]);
    mode_information->push_back("3: " + modes_[3]);
    mode_information->push_back("4: " + modes_[4]);
    mode_information->push_back("[compression]");
  }
  return true;
}

std::string MinizLibrary::GetModeName(const uint8_t &mode) {
  std::string result = "ERROR";
  if (mode < number_of_modes_) {
    result = modes_[mode];
  }
  return result;
}

MinizLibrary::MinizLibrary() {
  number_of_modes_ = 5;
  modes_ = new std::string[number_of_modes_];
  modes_[0] = "None";
  modes_[1] = "Filtered";
  modes_[2] = "Huffman";
  modes_[3] = "Rle";
  modes_[4] = "Fixed";
}

MinizLibrary::~MinizLibrary() { delete[] modes_; }
