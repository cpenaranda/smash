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

bool CompressionLibrary::CheckOptions(Options *options,
                                      const bool &compressor) {
  return true;
}

bool CompressionLibrary::SetOptionsCompressor(Options *options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) options_ = *options;
  return initialized_compressor_;
}

bool CompressionLibrary::SetOptionsDecompressor(Options *options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) options_ = *options;
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

bool CompressionLibrary::GetBackReferenceBitsInformation(
    std::vector<std::string> *back_reference_bits_information,
    uint8_t *minimum_bits, uint8_t *maximum_bits) {
  if (minimum_bits) *minimum_bits = 0;
  if (maximum_bits) *maximum_bits = 0;
  if (back_reference_bits_information) back_reference_bits_information->clear();
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

bool CompressionLibrary::CheckCompressionLevel(const std::string &library_name,
                                               Options *options,
                                               const uint8_t &minimum_level,
                                               const uint8_t &maximum_level) {
  bool result{true};
  if (options->CompressionLevelIsSet()) {
    if (minimum_level > 0 && options->GetCompressionLevel() < minimum_level) {
      std::cout << "ERROR: Compression level can not be lower than "
                << static_cast<uint64_t>(minimum_level) << " using "
                << library_name << std::endl;
      result = false;
    } else if (maximum_level >= 0 &&
               options->GetCompressionLevel() > maximum_level) {
      std::cout << "ERROR: Compression level can not be higher than "
                << static_cast<uint64_t>(maximum_level) << " using "
                << library_name << std::endl;
      result = false;
    }
  } else {
    options->SetCompressionLevel(minimum_level);
  }
  return result;
}

bool CompressionLibrary::CheckWindowSize(const std::string &library_name,
                                         Options *options,
                                         const uint32_t &minimum_size,
                                         const uint32_t &maximum_size) {
  bool result{true};
  if (options->WindowSizeIsSet()) {
    if (minimum_size > 0 && options->GetWindowSize() < minimum_size) {
      std::cout << "ERROR: Window size can not be lower than "
                << static_cast<uint64_t>(minimum_size) << " using "
                << library_name << std::endl;
      result = false;
    } else if (maximum_size > 0 && options->GetWindowSize() > maximum_size) {
      std::cout << "ERROR: Window size can not be higher than "
                << static_cast<uint64_t>(maximum_size) << " using "
                << library_name << std::endl;
      result = false;
    }
  } else {
    options->SetWindowSize(minimum_size);
  }
  return result;
}

bool CompressionLibrary::CheckMode(const std::string &library_name,
                                   Options *options,
                                   const uint8_t &minimum_mode,
                                   const uint8_t &maximum_mode) {
  bool result{true};
  if (options->ModeIsSet()) {
    if (minimum_mode > 0 && options->GetMode() < minimum_mode) {
      std::cout << "ERROR: Mode can not be lower than "
                << static_cast<uint64_t>(minimum_mode) << " using "
                << library_name << std::endl;
      result = false;
    } else if (maximum_mode > 0 && options->GetMode() > maximum_mode) {
      std::cout << "ERROR: Mode can not be higher than "
                << static_cast<uint64_t>(maximum_mode) << " using "
                << library_name << std::endl;
      result = false;
    }
  } else {
    options->SetMode(minimum_mode);
  }
  return result;
}

bool CompressionLibrary::CheckWorkFactor(const std::string &library_name,
                                         Options *options,
                                         const uint8_t &minimum_factor,
                                         const uint8_t &maximum_factor) {
  bool result{true};
  if (options->WorkFactorIsSet()) {
    if (minimum_factor > 0 && options->GetWorkFactor() < minimum_factor) {
      std::cout << "ERROR: Work factor can not be lower than "
                << static_cast<uint64_t>(minimum_factor) << " using "
                << library_name << std::endl;
      result = false;
    } else if (maximum_factor > 0 &&
               options->GetWorkFactor() > maximum_factor) {
      std::cout << "ERROR: Work factor can not be higher than "
                << static_cast<uint64_t>(maximum_factor) << " using "
                << library_name << std::endl;
      result = false;
    }
  } else {
    options->SetWorkFactor(minimum_factor);
  }
  return result;
}

bool CompressionLibrary::CheckFlags(const std::string &library_name,
                                    Options *options,
                                    const uint8_t &minimum_flags,
                                    const uint8_t &maximum_flags) {
  bool result{true};
  if (options->FlagsIsSet()) {
    if (minimum_flags > 0 && options->GetFlags() < minimum_flags) {
      std::cout << "ERROR: Flags can not be lower than "
                << static_cast<uint64_t>(minimum_flags) << " using "
                << library_name << std::endl;
      result = false;
    } else if (maximum_flags > 0 && options->GetFlags() > maximum_flags) {
      std::cout << "ERROR: Flags can not be higher than "
                << static_cast<uint64_t>(maximum_flags) << " using "
                << library_name << std::endl;
      result = false;
    }
  } else {
    options->SetFlags(minimum_flags);
  }
  return result;
}

bool CompressionLibrary::CheckNumberThreads(const std::string &library_name,
                                            Options *options,
                                            const uint8_t &minimum_threads,
                                            const uint8_t &maximum_threads) {
  bool result{true};
  if (options->NumberThreadsIsSet()) {
    if (minimum_threads > 0 && options->GetNumberThreads() < minimum_threads) {
      std::cout << "ERROR: Number of threads can not be lower than "
                << static_cast<uint64_t>(minimum_threads) << " using "
                << library_name << std::endl;
      result = false;
    } else if (maximum_threads > 0 &&
               options->GetNumberThreads() > maximum_threads) {
      std::cout << "ERROR: Number of threads can not be higher than "
                << static_cast<uint64_t>(maximum_threads) << " using "
                << library_name << std::endl;
      result = false;
    }
  } else {
    options->SetNumberThreads(minimum_threads);
  }
  return result;
}

bool CompressionLibrary::CheckBackReferenceBits(const std::string &library_name,
                                                Options *options,
                                                const uint8_t &minimum_bits,
                                                const uint8_t &maximum_bits) {
  bool result{true};
  if (options->BackReferenceBitsIsSet()) {
    if (minimum_bits > 0 && options->GetBackReferenceBits() < minimum_bits) {
      std::cout << "ERROR: Back refence bits can not be lower than "
                << static_cast<uint64_t>(minimum_bits) << " using "
                << library_name << std::endl;
      result = false;
    } else if (maximum_bits > 0 &&
               options->GetBackReferenceBits() > maximum_bits) {
      std::cout << "ERROR: Back refence bits can not be higher than "
                << static_cast<uint64_t>(maximum_bits) << " using "
                << library_name << std::endl;
      result = false;
    }
  } else {
    options->SetBackReferenceBits(minimum_bits);
  }
  return result;
}

Options CompressionLibrary::GetOptions() { return options_; }

CompressionLibrary::CompressionLibrary() {
  initialized_compressor_ = false;
  initialized_decompressor_ = false;
}

CompressionLibrary::~CompressionLibrary() {}
