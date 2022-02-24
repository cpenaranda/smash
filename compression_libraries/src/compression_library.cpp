/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <string.h>

#include <iomanip>

// SMASH LIBRARIES
#include <compression_library.hpp>

bool CompressionLibrary::CheckOptions(const Options &options,
                                      const bool &compressor) {
  return true;
}

bool CompressionLibrary::SetOptionsCompressor(const Options &options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) options_ = options;
  return initialized_compressor_;
}

bool CompressionLibrary::SetOptionsDecompressor(const Options &options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) options_ = options;
  return initialized_decompressor_;
}

void CompressionLibrary::GetCompressedDataSize(char *uncompressed_data,
                                               uint64_t uncompressed_size,
                                               uint64_t *compressed_size) {
  // There is no way to obtain with the library
  *compressed_size = ((uncompressed_size / 5000) + 1) * 5000;
}

void CompressionLibrary::GetDecompressedDataSize(char *compressed_data,
                                                 uint64_t compressed_size,
                                                 uint64_t *decompressed_size) {
  // There is no way to obtain with the library
}

void CompressionLibrary::GetTitle(const std::string &library_name,
                                  const std::string &description) {
  std::cout << std::left << std::setw(15) << std::setfill(' ') << library_name
            << "- " << description << std::endl;
}

bool CompressionLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 0;
  if (compression_level_information) compression_level_information->clear();
  return false;
}

bool CompressionLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool CompressionLibrary::GetModeInformation(
    std::vector<std::string> *mode_information, uint8_t *minimum_mode,
    uint8_t *maximum_mode, const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
  return false;
}

bool CompressionLibrary::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool CompressionLibrary::GetFlagsInformation(
    std::vector<std::string> *flags_information, uint8_t *minimum_flags,
    uint8_t *maximum_flags) {
  if (minimum_flags) *minimum_flags = 0;
  if (maximum_flags) *maximum_flags = 0;
  if (flags_information) flags_information->clear();
  return false;
}

bool CompressionLibrary::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

std::string CompressionLibrary::GetModeName(const uint8_t &mode) {
  return "------------";
}

std::string CompressionLibrary::GetFlagsName(const uint8_t &flags) {
  return "------------";
}

bool CompressionLibrary::CompareData(char *uncompress_data,
                                     const uint64_t &uncompress_size,
                                     char *decompress_data,
                                     const uint64_t &decompress_size) {
  return ((uncompress_size == decompress_size) &&
          (memcmp(uncompress_data, decompress_data, decompress_size) == 0));
}

bool CompressionLibrary::CheckCompressionLevel(std::string library_name,
                                               uint8_t level,
                                               uint8_t minimum_level,
                                               uint8_t maximum_level) {
  bool result{true};
  if (minimum_level > 0 && level < minimum_level) {
    std::cout << "ERROR: Compression level can not be lower than "
              << static_cast<uint64_t>(minimum_level) << " using "
              << library_name << std::endl;
    result = false;
  } else if (maximum_level >= 0 && level > maximum_level) {
    std::cout << "ERROR: Compression level can not be higher than "
              << static_cast<uint64_t>(maximum_level) << " using "
              << library_name << std::endl;
    result = false;
  }
  return result;
}

bool CompressionLibrary::CheckWindowSize(std::string library_name,
                                         uint32_t window_size,
                                         uint32_t minimum_size,
                                         uint32_t maximum_size) {
  bool result{true};
  if (minimum_size > 0 && window_size < minimum_size) {
    std::cout << "ERROR: Window size can not be lower than "
              << static_cast<uint64_t>(minimum_size) << " using "
              << library_name << std::endl;
    result = false;
  } else if (maximum_size > 0 && window_size > maximum_size) {
    std::cout << "ERROR: Window size can not be higher than "
              << static_cast<uint64_t>(maximum_size) << " using "
              << library_name << std::endl;
    result = false;
  }
  return result;
}

bool CompressionLibrary::CheckMode(std::string library_name, uint8_t mode,
                                   uint8_t minimum_mode, uint8_t maximum_mode) {
  bool result{true};
  if (minimum_mode > 0 && mode < minimum_mode) {
    std::cout << "ERROR: Mode can not be lower than "
              << static_cast<uint64_t>(minimum_mode) << " using "
              << library_name << std::endl;
    result = false;
  } else if (maximum_mode > 0 && mode > maximum_mode) {
    std::cout << "ERROR: Mode can not be higher than "
              << static_cast<uint64_t>(maximum_mode) << " using "
              << library_name << std::endl;
    result = false;
  }
  return result;
}

bool CompressionLibrary::CheckWorkFactor(std::string library_name,
                                         uint8_t work_factor,
                                         uint8_t minimum_factor,
                                         uint8_t maximum_factor) {
  bool result{true};
  if (minimum_factor > 0 && work_factor < minimum_factor) {
    std::cout << "ERROR: Work factor can not be lower than "
              << static_cast<uint64_t>(minimum_factor) << " using "
              << library_name << std::endl;
    result = false;
  } else if (maximum_factor > 0 && work_factor > maximum_factor) {
    std::cout << "ERROR: Work factor can not be higher than "
              << static_cast<uint64_t>(maximum_factor) << " using "
              << library_name << std::endl;
    result = false;
  }
  return result;
}

bool CompressionLibrary::CheckFlags(std::string library_name, uint8_t flags,
                                      uint8_t minimum_flags,
                                      uint8_t maximum_flags) {
  bool result{true};
  if (minimum_flags > 0 && flags < minimum_flags) {
    std::cout << "ERROR: Flags can not be lower than "
              << static_cast<uint64_t>(minimum_flags) << " using "
              << library_name << std::endl;
    result = false;
  } else if (maximum_flags > 0 && flags > maximum_flags) {
    std::cout << "ERROR: Flags can not be higher than "
              << static_cast<uint64_t>(maximum_flags) << " using "
              << library_name << std::endl;
    result = false;
  }
  return result;
}

bool CompressionLibrary::CheckNumberThreads(std::string library_name,
                                            uint8_t number_threads,
                                            uint8_t minimum_threads,
                                            uint8_t maximum_threads) {
  bool result{true};
  if (minimum_threads > 0 && number_threads < minimum_threads) {
    std::cout << "ERROR: Number of threads can not be lower than "
              << static_cast<uint64_t>(minimum_threads) << " using "
              << library_name << std::endl;
    result = false;
  } else if (maximum_threads > 0 && number_threads > maximum_threads) {
    std::cout << "ERROR: Number of threads can not be higher than "
              << static_cast<uint64_t>(maximum_threads) << " using "
              << library_name << std::endl;
    result = false;
  }
  return result;
}

CompressionLibrary::CompressionLibrary() {
  initialized_compressor_ = false;
  initialized_decompressor_ = false;
}
CompressionLibrary::~CompressionLibrary() {}
