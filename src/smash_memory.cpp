/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <unistd.h>

// SMASH LIBRARIES
#include <smash_memory.hpp>

SmashMemory::SmashMemory(const uint32_t &size)
    : size_(size),
      compression_library_data_(nullptr),
      compression_library_data_size_(0),
      status_(Status::ReadyForCommunicationLayer) {
  data_ = nullptr;
  if (posix_memalign(&data_, sysconf(_SC_PAGESIZE), size) != 0) {
    std::cout << "ERROR: Not enough memory" << std::endl;
    exit(EXIT_FAILURE);
  }
}

SmashMemory::~SmashMemory() {
  if (data_) free(data_);
}
