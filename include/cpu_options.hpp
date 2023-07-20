/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#pragma once

#include <iostream>

class CpuOptions {
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
  uint8_t back_reference_;
  bool back_reference_set_;

 public:
  void SetCompressionLevel(const uint8_t &compression_level);
  void SetWindowSize(const uint32_t &window_size);
  void SetMode(const uint8_t &mode);
  void SetWorkFactor(const uint8_t &work_factor);
  void SetFlags(const uint8_t &flags);
  void SetNumberThreads(const uint8_t &number_threads);
  void SetBackReference(const uint8_t &back_reference);

  bool CompressionLevelIsSet() const;
  bool WindowSizeIsSet() const;
  bool ModeIsSet() const;
  bool WorkFactorIsSet() const;
  bool FlagsIsSet() const;
  bool NumberThreadsIsSet() const;
  bool BackReferenceIsSet() const;

  uint8_t GetCompressionLevel() const;
  uint32_t GetWindowSize() const;
  uint8_t GetMode() const;
  uint8_t GetWorkFactor() const;
  uint8_t GetFlags() const;
  uint8_t GetNumberThreads() const;
  uint8_t GetBackReference() const;

  CpuOptions();
  ~CpuOptions();
};
