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

 public:
  void setCompressionLevel(const uint8_t &compression_level);
  void setWindowSize(const uint32_t &window_size);
  void setMode(const uint8_t &mode);
  void setWorkFactor(const uint8_t &work_factor);

  uint8_t getCompressionLevel();
  uint32_t getWindowSize();
  uint8_t getMode();
  uint8_t getWorkFactor();

  Options();
  ~Options();
};
