/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <iostream>

// SMASH LIBRARIES
#include <compression_libraries.hpp>

CompressionLibrary *CompressionLibraries::getCompressionLibrary(
    std::string library_name) {
  auto lib = map_.find(library_name);
  if (lib == map_.end()) {
    std::cout << "ERROR: The compression library does not exist" << std::endl;
    exit(EXIT_FAILURE);
  }
  return lib->second();
}

void CompressionLibraries::getListInformation() {
  CompressionLibrary *library;
  for (auto &lib : map_) {
    library = lib.second();
    library->getTitle();
    delete library;
  }
}

CompressionLibraries::CompressionLibraries() {}

CompressionLibraries::~CompressionLibraries() {}
