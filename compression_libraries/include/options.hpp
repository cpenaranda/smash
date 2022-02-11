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

 public:
  void setCompressionLevel(const uint8_t &compression_level);

  uint8_t getCompressionLevel();

  Options();
  ~Options();
};
