/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#pragma once

#include <iostream>

class Options {
 private:
  uint8_t compression_level_;
  uint32_t window_size_;
  uint8_t mode_;
  uint8_t work_factor_;
  uint8_t flags_;
  uint8_t number_threads_;
  uint8_t back_reference_bits_;

 public:
  void SetCompressionLevel(const uint8_t &compression_level);
  void SetWindowSize(const uint32_t &window_size);
  void SetMode(const uint8_t &mode);
  void SetWorkFactor(const uint8_t &work_factor);
  void SetFlags(const uint8_t &flags);
  void SetNumberThreads(const uint8_t &number_threads);
  void SetBackReferenceBits(const uint8_t &back_reference_bits);

  uint8_t GetCompressionLevel() const;
  uint32_t GetWindowSize() const;
  uint8_t GetMode() const;
  uint8_t GetWorkFactor() const;
  uint8_t GetFlags() const;
  uint8_t GetNumberThreads() const;
  uint8_t GetBackReferenceBits() const;

  Options();
  ~Options();
};
