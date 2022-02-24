/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */
#include <string.h>
extern "C" {
#include <z3lib.h>
// z3lib.h include typedefs to compile correctly with z3blib.h
#include <z3blib.h>
}

// SMASH LIBRARIES
#include <options.hpp>
#include <z3lib_library.hpp>

bool Z3libLibrary::CheckOptions(const Options &options,
                                const bool &compressor) {
  bool result{true};
  if (compressor) {
    result =
        CompressionLibrary::CheckShuffle("z3lib", options.GetShuffle(), 0, 3);
  }
  return result;
}

bool Z3libLibrary::SetOptionsCompressor(const Options &options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) options_ = options;
  return initialized_compressor_;
}

bool Z3libLibrary::SetOptionsDecompressor(const Options &options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) options_ = options;
  return initialized_decompressor_;
}

void Z3libLibrary::GetCompressedDataSize(char *uncompressed_data,
                                         uint64_t uncompressed_size,
                                         uint64_t *compressed_size) {
  // There is no way to obtain with Z3lib
  *compressed_size = ((uncompressed_size / 5000) + 1) * 5000;
}

bool Z3libLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                            char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t work_memory_size =
        Z3BE_MEMSIZE_MIN +
        ((options_.GetShuffle() & 2) ? Z3BE_MEMSIZE_EXTRA3 : 0);
    char *work_memory = new char[work_memory_size];
    uint64_t bytes{0};
    uint64_t final_compressed_size{0};
    z3be_weighing weighing;
    uint32_t inpipe;
    z3be_handle *handle =
        z3be_start(work_memory, work_memory_size, options_.GetShuffle() & 1,
                   options_.GetShuffle() & 2);
    if (result = handle) {
      while (uncompressed_size) {
        do {
          bytes = z3be_put(handle,
                           reinterpret_cast<unsigned char *>(uncompressed_data),
                           uncompressed_size);
          uncompressed_data += bytes;
          uncompressed_size -= bytes;
        } while (uncompressed_size && bytes);
        if (bytes) z3be_push(handle);
        z3be_tell(handle, &weighing, &inpipe);
        do {
          bytes = z3be_get(handle, &weighing,
                           reinterpret_cast<unsigned char *>(compressed_data),
                           *compressed_size - final_compressed_size);
          compressed_data += bytes;
          final_compressed_size += bytes;
        } while (bytes);
      }
      if (z3be_finish(handle,
                      reinterpret_cast<unsigned char *>(compressed_data))) {
        *compressed_size = final_compressed_size + 1;
      }
    } else {
      std::cout << "ERROR: z3lib error when compress data" << std::endl;
    }
    delete[] work_memory;
  }
  return result;
}

bool Z3libLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                              char *decompressed_data,
                              uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    char work_memory[Z3BD_MEMSIZE];
    unsigned char *auxiliar_decompressed_data{nullptr};
    uint64_t bytes{0};
    uint64_t final_decompressed_size{0};
    z3bd_handle *handle = z3bd_start(0, 0, work_memory, Z3BD_MEMSIZE);
    if (result = handle) {
      do {
        bytes =
            z3bd_put(handle, reinterpret_cast<unsigned char *>(compressed_data),
                     compressed_size);
        if (result = bytes) {
          compressed_data += bytes;
          compressed_size -= bytes;
          while ((bytes = z3bd_get(handle, &auxiliar_decompressed_data)) > 0 &&
                 result) {
            if (final_decompressed_size == *decompressed_size) {
              result = false;
            } else {
              memcpy(decompressed_data, auxiliar_decompressed_data, bytes);
              decompressed_data += bytes;
              final_decompressed_size += bytes;
            }
          }
          if (!auxiliar_decompressed_data) {
            if (z3bd_finish(handle, reinterpret_cast<unsigned int *>(&bytes),
                            reinterpret_cast<int *>(&bytes)) ==
                    z3err_bd_notbfinal &&
                !compressed_size) {
              result = false;
            }
          }
        }
      } while (compressed_size && result);
      if (result) {
        result = (z3bd_finish(handle, reinterpret_cast<unsigned int *>(&bytes),
                              reinterpret_cast<int *>(&bytes)) == z3err_none);
      }
    }
    if (!result) {
      std::cout << "ERROR: z3lib error when decompress data" << std::endl;
    }
    *decompressed_size = final_decompressed_size;
  }
  return result;
}

void Z3libLibrary::GetDecompressedDataSize(char *compressed_data,
                                           uint64_t compressed_size,
                                           uint64_t *decompressed_size) {
  // There is no way to obtain with Z3lib
}

void Z3libLibrary::GetTitle() { CompressionLibrary::GetTitle("z3lib", ""); }

bool Z3libLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 0;
  if (compression_level_information) compression_level_information->clear();
  return false;
}

bool Z3libLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 0;
  if (maximum_size) *maximum_size = 0;
  if (window_size_information) window_size_information->clear();
  return false;
}

bool Z3libLibrary::GetModeInformation(
    std::vector<std::string> *mode_information, uint8_t *minimum_mode,
    uint8_t *maximum_mode, const uint8_t &compression_level) {
  if (minimum_mode) *minimum_mode = 0;
  if (maximum_mode) *maximum_mode = 0;
  if (mode_information) mode_information->clear();
  return false;
}

bool Z3libLibrary::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  if (minimum_factor) *minimum_factor = 0;
  if (maximum_factor) *maximum_factor = 0;
  if (work_factor_information) work_factor_information->clear();
  return false;
}

bool Z3libLibrary::GetShuffleInformation(
    std::vector<std::string> *shuffle_information, uint8_t *minimum_shuffle,
    uint8_t *maximum_shuffle) {
  if (minimum_shuffle) *minimum_shuffle = 0;
  if (maximum_shuffle) *maximum_shuffle = 3;
  if (shuffle_information) {
    shuffle_information->clear();
    shuffle_information->push_back("Available values [0-3]");
    shuffle_information->push_back("0: " + shuffles_[0]);
    shuffle_information->push_back("1: " + shuffles_[1] + " match");
    shuffle_information->push_back(
        "2: " + shuffles_[2] + " for codes with length 3 and large distance");
    shuffle_information->push_back("3: " + shuffles_[3] + " flags");
    shuffle_information->push_back("[compression]");
  }
  return true;
}

bool Z3libLibrary::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  if (minimum_threads) *minimum_threads = 0;
  if (maximum_threads) *maximum_threads = 0;
  if (number_threads_information) number_threads_information->clear();
  return false;
}

std::string Z3libLibrary::GetModeName(const uint8_t &mode) {
  return CompressionLibrary::GetDefaultModeName();
}

std::string Z3libLibrary::GetShuffleName(const uint8_t &shuffle) {
  std::string result = CompressionLibrary::GetDefaultShuffleName();
  if (shuffle < number_of_shuffles_) {
    result = shuffles_[shuffle];
  }
  return result;
}

Z3libLibrary::Z3libLibrary() {
  number_of_shuffles_ = 4;
  shuffles_ = new std::string[number_of_shuffles_];
  shuffles_[0] = "None";
  shuffles_[1] = "Prefer longer";
  shuffles_[2] = "Limit length";
  shuffles_[3] = "1 & 2";
}

Z3libLibrary::~Z3libLibrary() { delete[] shuffles_; }
