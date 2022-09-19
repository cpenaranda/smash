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

bool Z3libLibrary::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckFlags("z3lib", options, 0, 3);
  }
  return result;
}

bool Z3libLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                            char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t work_memory_size =
        Z3BE_MEMSIZE_MIN +
        ((options_.GetFlags() & 2) ? Z3BE_MEMSIZE_EXTRA3 : 0);
    char *work_memory = new char[work_memory_size];
    uint64_t bytes{0};
    uint64_t final_compressed_size{0};
    z3be_weighing weighing;
    uint32_t inpipe;
    z3be_handle *handle =
        z3be_start(work_memory, work_memory_size, options_.GetFlags() & 1,
                   options_.GetFlags() & 2);
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
      } else {
        *compressed_size = final_compressed_size;
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
    int error{0};
    uint64_t final_decompressed_size{0};
    z3bd_handle *handle = z3bd_start(0, 0, work_memory, Z3BD_MEMSIZE);
    if (result = handle) {
      while (compressed_size && result) {
        do {
          bytes = z3bd_put(handle,
                           reinterpret_cast<unsigned char *>(compressed_data),
                           compressed_size);
          compressed_data += bytes;
          compressed_size -= bytes;
        } while (compressed_size && bytes);
        do {
          bytes = z3bd_get(handle, &auxiliar_decompressed_data);
          if (bytes) {
            memcpy(decompressed_data, auxiliar_decompressed_data, bytes);
            decompressed_data += bytes;
            final_decompressed_size += bytes;
          }
        } while (bytes);
        if (!auxiliar_decompressed_data) {
          error = z3bd_finish(handle, reinterpret_cast<unsigned int *>(&bytes),
                              reinterpret_cast<int *>(&bytes));
          result = (error == z3err_bd_notbfinal) || (error == z3err_none);
        }
      }
    }
    if (!result) {
      std::cout << "ERROR: z3lib error when decompress data" << std::endl;
    }
    *decompressed_size = final_decompressed_size;
  }
  return result;
}

void Z3libLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "z3lib", "Substitute for the well known zlib compression library");
}

bool Z3libLibrary::GetFlagsInformation(
    std::vector<std::string> *flags_information, uint8_t *minimum_flags,
    uint8_t *maximum_flags) {
  if (minimum_flags) *minimum_flags = 0;
  if (maximum_flags) *maximum_flags = 3;
  if (flags_information) {
    flags_information->clear();
    flags_information->push_back("Available values [0-3]");
    flags_information->push_back("0: " + flags_[0]);
    flags_information->push_back("1: " + flags_[1] + " match");
    flags_information->push_back("2: " + flags_[2] +
                                 " for codes with length 3 and large distance");
    flags_information->push_back("3: " + flags_[3] + " flags");
    flags_information->push_back("[compression]");
  }
  return true;
}

std::string Z3libLibrary::GetFlagsName(const uint8_t &flags) {
  std::string result = "ERROR";
  if (flags < number_of_flags_) {
    result = flags_[flags];
  }
  return result;
}

Z3libLibrary::Z3libLibrary() {
  number_of_flags_ = 4;
  flags_ = new std::string[number_of_flags_];
  flags_[0] = "None";
  flags_[1] = "Prefer longer";
  flags_[2] = "Limit length";
  flags_[3] = "1 & 2";
}

Z3libLibrary::~Z3libLibrary() { delete[] flags_; }
