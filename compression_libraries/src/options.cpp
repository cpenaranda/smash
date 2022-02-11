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

uint8_t Options::getCompressionLevel() { return compression_level_; }

uint32_t Options::getWindowSize() { return window_size_; }

uint8_t Options::getMode() { return mode_; }

Options::Options() {
  compression_level_ = 1;
  window_size_ = 10;
  mode_ = 0;
}

Options::~Options() {}
