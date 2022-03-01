/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

// SMASH LIBRARIES
#include <result.hpp>

Result::Result(const std::string &message, const uint64_t &uncompressed_size,
               const uint64_t &compressed_size, const double &compression_vel,
               const double &decompression_vel, const double &total_vel,
               const uint8_t &option)
    : message_(message),
      uncompressed_size_(uncompressed_size),
      compressed_size_(compressed_size),
      compression_vel_(compression_vel),
      decompression_vel_(decompression_vel),
      total_vel_(total_vel),
      option_(option) {}

bool Result::operator<(const Result &other) const {
  bool result{false};
  if (option_ == 1) {
    // Compression Ratio
    result = other.compressed_size_ < compressed_size_;
  } else if (option_ == 2) {
    if (other.compressed_size_ < other.uncompressed_size_) {
      // Compression Time
      result = other.compression_vel_ > compression_vel_;
    }
  } else if (option_ == 3) {
    if (other.compressed_size_ < other.uncompressed_size_) {
      // Decompression Time
      result = other.decompression_vel_ > decompression_vel_;
    }
  } else if (option_ == 4) {
    if (other.compressed_size_ < other.uncompressed_size_) {
      // Total Time
      result = other.total_vel_ > total_vel_;
    }
  }
  return result;
}
