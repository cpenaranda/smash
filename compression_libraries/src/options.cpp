/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

// SMASH LIBRARIES
#include <options.hpp>

bool Options::SetCompressionLevel(const uint8_t &compression_level) {
  compression_level_ = compression_level;
  bool result = compression_level_set_;
  compression_level_set_ = true;
  return result;
}

bool Options::SetWindowSize(const uint32_t &window_size) {
  window_size_ = window_size;
  bool result = window_size_set_;
  window_size_set_ = true;
  return result;
}

bool Options::SetMode(const uint8_t &mode) {
  mode_ = mode;
  bool result = mode_set_;
  mode_set_ = true;
  return result;
}

bool Options::SetWorkFactor(const uint8_t &work_factor) {
  work_factor_ = work_factor;
  bool result = work_factor_set_;
  work_factor_set_ = true;
  return result;
}

bool Options::SetFlags(const uint8_t &flags) {
  flags_ = flags;
  bool result = flags_set_;
  flags_set_ = true;
  return result;
}

bool Options::SetNumberThreads(const uint8_t &number_threads) {
  number_threads_ = number_threads;
  bool result = number_threads_set_;
  number_threads_set_ = true;
  return result;
}

bool Options::SetBackReferenceBits(const uint8_t &back_reference_bits) {
  back_reference_bits_ = back_reference_bits;
  bool result = back_reference_bits_set_;
  back_reference_bits_set_ = true;
  return result;
}

bool Options::CompressionLevelIsSet() const { return compression_level_set_; }

bool Options::WindowSizeIsSet() const { return window_size_set_; }

bool Options::ModeIsSet() const { return mode_set_; }

bool Options::WorkFactorIsSet() const { return work_factor_set_; }

bool Options::FlagsIsSet() const { return flags_set_; }

bool Options::NumberThreadsIsSet() const { return number_threads_set_; }

bool Options::BackReferenceBitsIsSet() const {
  return back_reference_bits_set_;
}

uint8_t Options::GetCompressionLevel() const { return compression_level_; }

uint32_t Options::GetWindowSize() const { return window_size_; }

uint8_t Options::GetMode() const { return mode_; }

uint8_t Options::GetWorkFactor() const { return work_factor_; }

uint8_t Options::GetFlags() const { return flags_; }

uint8_t Options::GetNumberThreads() const { return number_threads_; }

uint8_t Options::GetBackReferenceBits() const { return back_reference_bits_; }

Options::Options() {
  compression_level_ = 0;
  compression_level_set_ = false;
  window_size_ = 0;
  window_size_set_ = false;
  mode_ = 0;
  mode_set_ = false;
  work_factor_ = 0;
  work_factor_set_ = false;
  flags_ = 0;
  flags_set_ = false;
  number_threads_ = 0;
  number_threads_set_ = false;
  back_reference_bits_ = 0;
  back_reference_bits_set_ = false;
}

Options::~Options() {}
