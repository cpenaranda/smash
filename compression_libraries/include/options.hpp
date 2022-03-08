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
  bool compression_level_set_;
  uint32_t window_size_;
  bool window_size_set_;
  uint8_t mode_;
  bool mode_set_;
  uint8_t work_factor_;
  bool work_factor_set_;
  uint8_t flags_;
  bool flags_set_;
  uint8_t number_threads_;
  bool number_threads_set_;
  uint8_t back_reference_bits_;
  bool back_reference_bits_set_;

 public:
  bool SetCompressionLevel(const uint8_t &compression_level);
  bool SetWindowSize(const uint32_t &window_size);
  bool SetMode(const uint8_t &mode);
  bool SetWorkFactor(const uint8_t &work_factor);
  bool SetFlags(const uint8_t &flags);
  bool SetNumberThreads(const uint8_t &number_threads);
  bool SetBackReferenceBits(const uint8_t &back_reference_bits);

  bool CompressionLevelIsSet() const;
  bool WindowSizeIsSet() const;
  bool ModeIsSet() const;
  bool WorkFactorIsSet() const;
  bool FlagsIsSet() const;
  bool NumberThreadsIsSet() const;
  bool BackReferenceBitsIsSet() const;

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
