/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

// SMASH LIBRARIES
#include <options.hpp>

void Options::SetCompressionLevel(const uint8_t &compression_level) {
  compression_level_ = compression_level;
}

void Options::SetWindowSize(const uint32_t &window_size) {
  window_size_ = window_size;
}

void Options::SetMode(const uint8_t &mode) { mode_ = mode; }

void Options::SetWorkFactor(const uint8_t &work_factor) {
  work_factor_ = work_factor;
}

void Options::SetFlags(const uint8_t &flags) { flags_ = flags; }

void Options::SetNumberThreads(const uint8_t &number_threads) {
  number_threads_ = number_threads;
}

void Options::SetBackReferenceBits(const uint8_t &back_reference_bits) {
  back_reference_bits_ = back_reference_bits;
}

uint8_t Options::GetCompressionLevel() const { return compression_level_; }

uint32_t Options::GetWindowSize() const { return window_size_; }

uint8_t Options::GetMode() const { return mode_; }

uint8_t Options::GetWorkFactor() const { return work_factor_; }

uint8_t Options::GetFlags() const { return flags_; }

uint8_t Options::GetNumberThreads() const { return number_threads_; }

uint8_t Options::GetBackReferenceBits() const { return back_reference_bits_; }

Options::Options() {
  compression_level_ = 1;
  window_size_ = 15;
  mode_ = 1;
  work_factor_ = 30;
  flags_ = 0;
  number_threads_ = 1;
  back_reference_bits_ = 4;
}

Options::~Options() {}
