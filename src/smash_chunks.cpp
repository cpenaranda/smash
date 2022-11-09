/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

// SMASH LIBRARIES
#include <smash_chunks.hpp>
#include <smash_memory.hpp>

SmashChunks::SmashChunks(const uint16_t &number_of_chunks,
                         const uint32_t &chunk_size)
    : number_of_chunks_(number_of_chunks),
      chunk_size_(chunk_size),
      first_available_for_compression_library_(0),
      first_available_for_communication_layer_(0),
      first_available_to_set_(0) {
  chunks_.reserve(number_of_chunks);
  for (uint16_t i = 0; i < number_of_chunks; ++i) {
    chunks_.push_back(std::make_shared<SmashMemory>(chunk_size));
  }
}

SmashChunks::~SmashChunks() {}
