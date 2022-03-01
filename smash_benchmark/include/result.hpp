/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#pragma once

#include <iostream>
#include <string>

class Result {
 public:
  std::string message_;
  uint64_t uncompressed_size_;
  uint64_t compressed_size_;
  double compression_vel_;
  double decompression_vel_;
  double total_vel_;
  uint8_t option_;

  Result(const std::string &message, const uint64_t &uncompressed_size = 0,
         const uint64_t &compressed_size = 0, const double &compression_vel = 0,
         const double &decompression_vel = 0, const double &total_vel = 0,
         const uint8_t &option = 0);

  bool operator<(const Result &other) const;
};
