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
#include <queue>
#include <string>
#include <thread>  // NOLINT
#include <vector>

// SMASH LIBRARIES
#include <options.hpp>
#include <smash.hpp>
#include <smash_chunks.hpp>
#include <smash_connection.hpp>

class SmashNetwork {
 private:
  Options options_compressor_;
  Options options_decompressor_;

  uint8_t threads_to_work_;
  std::string library_name_compressor_;
  std::vector<std::shared_ptr<Smash>> compressors_;

  std::string library_name_decompressor_;
  std::vector<std::shared_ptr<Smash>> decompressors_;

  uint32_t chunk_size_;
  uint16_t number_of_chunks_;
  std::shared_ptr<SmashChunks> chunks_;

  std::vector<std::thread> threads_;

  SmashConnection connection_;

  static bool Compress(std::shared_ptr<Smash> compressor,
                       std::shared_ptr<SmashMemory> memory);

  static bool Decompress(std::shared_ptr<Smash> decompressor,
                         std::shared_ptr<SmashMemory> memory);

  static void StreamBehaviour(std::shared_ptr<Smash> compressor,
                              std::shared_ptr<Smash> decompressor,
                              std::shared_ptr<SmashChunks> chunks_);

 public:
  bool Connect(const int &socket);

  int Write_v1(void *buffer, const uint32_t &number_bytes,
               uint64_t *compressed_size, const bool &ack = false);
  int Read_v1(void *buffer, const uint32_t &number_bytes,
              const bool &ack = false);

  bool Initilize();

  void RemoveStreams();

  SmashNetwork(const std::string &compression_library_name,
               const Options &options, const uint8_t &threads_to_work = 0,
               const uint32_t &chunk_size = 0,
               const uint16_t &number_of_chunks = 0);

  ~SmashNetwork();
};
