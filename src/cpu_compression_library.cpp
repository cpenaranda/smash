/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <string.h>

#include <iomanip>

// CPU-SMASH LIBRARIES
#include <cpu_compression_library.hpp>

bool CpuCompressionLibrary::CheckOptions(CpuOptions *options,
                                         const bool &compressor) {
  return true;
}

bool CpuCompressionLibrary::SetOptionsCompressor(CpuOptions *options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) options_ = *options;
  return initialized_compressor_;
}

bool CpuCompressionLibrary::SetOptionsDecompressor(CpuOptions *options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) options_ = *options;
  return initialized_decompressor_;
}

void CpuCompressionLibrary::GetCompressedDataSize(
    const char *const uncompressed_data, const uint64_t &uncompressed_data_size,
    uint64_t *compressed_data_size) {
  // There is no way to obtain with the library
  if (uncompressed_data_size < 2500) {
    *compressed_data_size = 5000;
  } else {
    *compressed_data_size = uncompressed_data_size * 2;
  }
}

void CpuCompressionLibrary::GetDecompressedDataSize(
    const char *const compressed_data, const uint64_t &compressed_data_size,
    uint64_t *decompressed_data_size) {
  // There is no way to obtain with the library
}

void CpuCompressionLibrary::GetTitle(const std::string &library_name,
                                     const std::string &description) {
  std::cout << std::left << std::setw(15) << std::setfill(' ') << library_name
            << "- " << description << std::endl;
}

bool CpuCompressionLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 0;
  if (compression_level_information) compression_level_information->clear();
  return false;
}

bool CpuCompressionLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool CpuCompressionLibrary::GetModeInformation(
    std::vector<std::string> *mode_information, uint8_t *minimum_mode,
    uint8_t *maximum_mode, const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
  return false;
}

bool CpuCompressionLibrary::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool CpuCompressionLibrary::GetFlagsInformation(
    std::vector<std::string> *flags_information, uint8_t *minimum_flags,
    uint8_t *maximum_flags) {
  if (minimum_flags) *minimum_flags = 0;
  if (maximum_flags) *maximum_flags = 0;
  if (flags_information) flags_information->clear();
  return false;
}

bool CpuCompressionLibrary::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

bool CpuCompressionLibrary::GetBackReferenceInformation(
    std::vector<std::string> *back_reference_information,
    uint8_t *minimum_back_reference, uint8_t *maximum_back_reference) {
  if (minimum_back_reference) *minimum_back_reference = 0;
  if (maximum_back_reference) *maximum_back_reference = 0;
  if (back_reference_information) back_reference_information->clear();
  return false;
}

std::string CpuCompressionLibrary::GetModeName(const uint8_t &mode) {
  return "------------";
}

std::string CpuCompressionLibrary::GetFlagsName(const uint8_t &flags) {
  return "------------";
}

bool CpuCompressionLibrary::CompareData(
    const char *const uncompressed_data, const uint64_t &uncompressed_data_size,
    const char *const decompressed_data,
    const uint64_t &decompressed_data_size) {
  return ((uncompressed_data_size == decompressed_data_size) &&
          (memcmp(uncompressed_data, decompressed_data,
                  decompressed_data_size) == 0));
}

bool CpuCompressionLibrary::CheckCompressionLevel(
    const std::string &library_name, CpuOptions *options,
    const uint8_t &minimum_level, const uint8_t &maximum_level) {
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

bool CpuCompressionLibrary::CheckWindowSize(const std::string &library_name,
                                            CpuOptions *options,
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

bool CpuCompressionLibrary::CheckMode(const std::string &library_name,
                                      CpuOptions *options,
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

bool CpuCompressionLibrary::CheckWorkFactor(const std::string &library_name,
                                            CpuOptions *options,
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

bool CpuCompressionLibrary::CheckFlags(const std::string &library_name,
                                       CpuOptions *options,
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

bool CpuCompressionLibrary::CheckNumberThreads(const std::string &library_name,
                                               CpuOptions *options,
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

bool CpuCompressionLibrary::CheckBackReference(
    const std::string &library_name, CpuOptions *options,
    const uint8_t &minimum_back_reference,
    const uint8_t &maximum_back_reference) {
  bool result{true};
  if (options->BackReferenceIsSet()) {
    if (minimum_back_reference > 0 &&
        options->GetBackReference() < minimum_back_reference) {
      std::cout << "ERROR: Back refence bits can not be lower than "
                << static_cast<uint64_t>(minimum_back_reference) << " using "
                << library_name << std::endl;
      result = false;
    } else if (maximum_back_reference > 0 &&
               options->GetBackReference() > maximum_back_reference) {
      std::cout << "ERROR: Back refence bits can not be higher than "
                << static_cast<uint64_t>(maximum_back_reference) << " using "
                << library_name << std::endl;
      result = false;
    }
  } else {
    options->SetBackReference(minimum_back_reference);
  }
  return result;
}

CpuOptions CpuCompressionLibrary::GetOptions() { return options_; }

CpuCompressionLibrary::CpuCompressionLibrary() {
  initialized_compressor_ = false;
  initialized_decompressor_ = false;
}

CpuCompressionLibrary::~CpuCompressionLibrary() {}
