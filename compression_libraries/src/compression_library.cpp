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

void CompressionLibrary::GetTitle(const std::string &library_name,
                                  const std::string &description) {
  std::cout << std::left << std::setw(15) << std::setfill(' ') << library_name
            << "- " << description << std::endl;
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

bool CompressionLibrary::CheckShuffle(std::string library_name, uint8_t shuffle,
                                      uint8_t minimum_shuffle,
                                      uint8_t maximum_shuffle) {
  bool result{true};
  if (minimum_shuffle > 0 && shuffle < minimum_shuffle) {
    std::cout << "ERROR: Shuffle can not be lower than "
              << static_cast<uint64_t>(minimum_shuffle) << " using "
              << library_name << std::endl;
    result = false;
  } else if (maximum_shuffle > 0 && shuffle > maximum_shuffle) {
    std::cout << "ERROR: Shuffle can not be higher than "
              << static_cast<uint64_t>(maximum_shuffle) << " using "
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

std::string CompressionLibrary::GetDefaultModeName() { return "------------"; }

std::string CompressionLibrary::GetDefaultShuffleName() {
  return "------------";
}

CompressionLibrary::CompressionLibrary() {
  initialized_compressor_ = false;
  initialized_decompressor_ = false;
}
CompressionLibrary::~CompressionLibrary() {}
