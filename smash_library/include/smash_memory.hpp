/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#pragma once

#include <iostream>

class SmashMemory {
 public:
  enum class Status {
    // Data can be compressed
    ReadyForCompression,
    // Data can be decompressed
    ReadyForDecompression,
    // Data is being compressed
    Compressing,
    // Data is being transferred
    Transferring,
    // Data is being decompressed
    Decompressing,
    // Data can be transferred
    ReadyForCommunicationLayer,
    // Some error occurs
    Error,
    // Indicates threads must finish
    End
  };

  char *GetData();
  char *GetCompressionLibraryData();
  void SetCompressionLibraryData(void *data);

  uint32_t GetSize();
  uint32_t GetCompressionLibraryDataSize();
  uint32_t GetDecompressionLibraryDataSize();
  void SetCompressionLibraryDataSize(const uint32_t &data_size);
  void SetDecompressionLibraryDataSize(const uint32_t &data_size);

  Status GetStatus();
  void SetStatus(const Status &status);

  explicit SmashMemory(const uint32_t &size);
  ~SmashMemory();

 private:
  void *data_;
  uint32_t size_;
  void *compression_library_data_;
  uint32_t compression_library_data_size_;
  uint32_t decompression_library_data_size_;
  Status status_;
};

#include <smash_memory.inl>  // NOLINT
