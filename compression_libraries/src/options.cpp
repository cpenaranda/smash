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

uint8_t Options::getCompressionLevel() { return compression_level_; }

Options::Options() { compression_level_ = 1; }

Options::~Options() {}
