/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#pragma once

#include <condition_variable>  // NOLINT
#include <iostream>
#include <memory>
#include <mutex>  // NOLINT
#include <vector>

// SMASH LIBRARIES
#include <smash_memory.hpp>

class SmashChunks {
 private:
  std::mutex mutex_for_compression_library_;
  std::mutex mutex_for_communication_layer_;
  std::condition_variable condition_for_compression_library_;
  std::condition_variable condition_for_communication_layer_;
  uint32_t chunk_size_;
  uint16_t number_of_chunks_;
  uint16_t first_available_for_compression_library_;
  uint16_t first_available_for_communication_layer_;
  uint16_t first_available_to_set_;
  std::vector<std::shared_ptr<SmashMemory>> chunks_;

 public:
  std::shared_ptr<SmashMemory> GetNextMemoryForCompressionLibrary();
  std::shared_ptr<SmashMemory> GetNextMemoryForCommunicationLayer();

  void SetNextMemoryForCompressionLibrary(std::shared_ptr<SmashMemory> memory,
                                          void *data,
                                          const uint32_t &data_size);
  bool SetNextMemoryForCompressionLibrary(void *data,
                                          const uint32_t &data_size);
  void SetNextMemoryForCommunicationLayer(std::shared_ptr<SmashMemory> memory,
                                          const bool &status);

  bool Synchronize();

  void TheEnd();

  SmashChunks(const uint16_t &number_of_chunks, const uint32_t &chunk_size);
  ~SmashChunks();
};

#include <smash_chunks.inl>  // NOLINT
