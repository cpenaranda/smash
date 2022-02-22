/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <iostream>

// SMASH LIBRARIES
#include <brieflz_library.hpp>
#include <brotli_library.hpp>
#include <bzip2_library.hpp>
#include <c-blosc2_library.hpp>
#include <compression_libraries.hpp>
#include <density_library.hpp>
#include <fari_library.hpp>
#include <flz_library.hpp>
#include <gipfeli_library.hpp>
#include <libdeflate_library.hpp>
#include <lzf_library.hpp>
#include <lzfse_library.hpp>
#include <lzfx_library.hpp>
#include <lzma_library.hpp>
#include <lzo_library.hpp>
#include <ms_library.hpp>
#include <snappy_library.hpp>
#include <xpack_library.hpp>
#include <zlib-ng_library.hpp>
#include <zlib_library.hpp>
#include <zstd_library.hpp>

CompressionLibrary *CompressionLibraries::GetCompressionLibrary(
    std::string library_name) {
  auto lib = map_.find(library_name);
  if (lib == map_.end()) {
    std::cout << "ERROR: The compression library does not exist" << std::endl;
    exit(EXIT_FAILURE);
  }
  return lib->second();
}

void CompressionLibraries::GetListInformation() {
  CompressionLibrary *library;
  for (auto &lib : map_) {
    library = lib.second();
    library->GetTitle();
    delete library;
  }
}

std::vector<std::string> CompressionLibraries::GetNameLibraries() {
  std::vector<std::string> result;
  for (auto &lib : map_) {
    result.push_back(lib.first);
  }
  return result;
}

CompressionLibraries::CompressionLibraries() {
  map_["brieflz"] = []() { return new BrieflzLibrary(); };
  map_["brotli"] = []() { return new BrotliLibrary(); };
  map_["bzip2"] = []() { return new Bzip2Library(); };
  map_["c-blosc2"] = []() { return new CBlosc2Library(); };
  map_["density"] = []() { return new DensityLibrary(); };
  map_["fari"] = []() { return new FariLibrary(); };
  map_["flz"] = []() { return new FlzLibrary(); };
  map_["gipfeli"] = []() { return new GipfeliLibrary(); };
  map_["libdeflate"] = []() { return new LibdeflateLibrary(); };
  map_["lzf"] = []() { return new LzfLibrary(); };
  map_["lzfse"] = []() { return new LzfseLibrary(); };
  map_["lzfx"] = []() { return new LzfxLibrary(); };
  map_["lzma"] = []() { return new LzmaLibrary(); };
  map_["lzo"] = []() { return new LzoLibrary(); };
  map_["ms"] = []() { return new MsLibrary(); };
  map_["snappy"] = []() { return new SnappyLibrary(); };
  map_["xpack"] = []() { return new XpackLibrary(); };
  map_["zlib"] = []() { return new ZlibLibrary(); };
  map_["zlib-ng"] = []() { return new ZlibNgLibrary(); };
  map_["zstd"] = []() { return new ZstdLibrary(); };
}

CompressionLibraries::~CompressionLibraries() {}
