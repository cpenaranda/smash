/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

// SMASH LIBRARIES
#include <options.hpp>

void Options::setCompressionLevel(const uint8_t &compression_level) {
  compression_level_ = compression_level;
}

void Options::setWindowSize(const uint32_t &window_size) {
  window_size_ = window_size;
}

void Options::setMode(const uint8_t &mode) { mode_ = mode; }

void Options::setWorkFactor(const uint8_t &work_factor) {
  work_factor_ = work_factor;
}

void Options::setShuffle(const uint8_t &shuffle) { shuffle_ = shuffle; }

void Options::setNumberThreads(const uint8_t &number_threads) {
  number_threads_ = number_threads;
}

void Options::setBackReferenceBits(const uint8_t &back_reference_bits) {
  back_reference_bits_ = back_reference_bits;
}

uint8_t Options::getCompressionLevel() { return compression_level_; }

uint32_t Options::getWindowSize() { return window_size_; }

uint8_t Options::getMode() { return mode_; }

uint8_t Options::getWorkFactor() { return work_factor_; }

uint8_t Options::getShuffle() { return shuffle_; }

uint8_t Options::getNumberThreads() { return number_threads_; }

uint8_t Options::getBackReferenceBits() { return back_reference_bits_; }

Options::Options() {
  compression_level_ = 1;
  window_size_ = 10;
  mode_ = 0;
  work_factor_ = 30;
  shuffle_ = 0;
  number_threads_ = 1;
  back_reference_bits_ = 4;
}

Options::~Options() {}
