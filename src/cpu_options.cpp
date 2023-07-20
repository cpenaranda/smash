/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>

void CpuOptions::SetCompressionLevel(const uint8_t &compression_level) {
  compression_level_ = compression_level;
  compression_level_set_ = true;
}

void CpuOptions::SetWindowSize(const uint32_t &window_size) {
  window_size_ = window_size;
  window_size_set_ = true;
}

void CpuOptions::SetMode(const uint8_t &mode) {
  mode_ = mode;
  mode_set_ = true;
}

void CpuOptions::SetWorkFactor(const uint8_t &work_factor) {
  work_factor_ = work_factor;
  work_factor_set_ = true;
}

void CpuOptions::SetFlags(const uint8_t &flags) {
  flags_ = flags;
  flags_set_ = true;
}

void CpuOptions::SetNumberThreads(const uint8_t &number_threads) {
  number_threads_ = number_threads;
  number_threads_set_ = true;
}

void CpuOptions::SetBackReference(const uint8_t &back_reference) {
  back_reference_ = back_reference;
  back_reference_set_ = true;
}

bool CpuOptions::CompressionLevelIsSet() const {
  return compression_level_set_;
}

bool CpuOptions::WindowSizeIsSet() const { return window_size_set_; }

bool CpuOptions::ModeIsSet() const { return mode_set_; }

bool CpuOptions::WorkFactorIsSet() const { return work_factor_set_; }

bool CpuOptions::FlagsIsSet() const { return flags_set_; }

bool CpuOptions::NumberThreadsIsSet() const { return number_threads_set_; }

bool CpuOptions::BackReferenceIsSet() const { return back_reference_set_; }

uint8_t CpuOptions::GetCompressionLevel() const { return compression_level_; }

uint32_t CpuOptions::GetWindowSize() const { return window_size_; }

uint8_t CpuOptions::GetMode() const { return mode_; }

uint8_t CpuOptions::GetWorkFactor() const { return work_factor_; }

uint8_t CpuOptions::GetFlags() const { return flags_; }

uint8_t CpuOptions::GetNumberThreads() const { return number_threads_; }

uint8_t CpuOptions::GetBackReference() const { return back_reference_; }

CpuOptions::CpuOptions() {
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
  back_reference_ = 0;
  back_reference_set_ = false;
}

CpuOptions::~CpuOptions() {}
