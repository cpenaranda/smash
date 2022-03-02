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
#include <csc_library.hpp>
#include <density_library.hpp>
#include <fari_library.hpp>
#include <flz_library.hpp>
#include <gipfeli_library.hpp>
#include <heatshrink_library.hpp>
#include <libbsc_library.hpp>
#include <libdeflate_library.hpp>
#include <liblzg_library.hpp>
#include <lz4_library.hpp>
#include <lzf_library.hpp>
#include <lzfse_library.hpp>
#include <lzfx_library.hpp>
#include <lzham_library.hpp>
#include <lzjb_library.hpp>
#include <lzma_library.hpp>
#include <lzo_library.hpp>
#include <miniz_library.hpp>
#include <ms_library.hpp>
#include <quicklz_library.hpp>
#include <snappy_library.hpp>
#include <wflz_library.hpp>
#include <xpack_library.hpp>
#include <yalz77_library.hpp>
#include <z3lib_library.hpp>
#include <zlib-ng_library.hpp>
#include <zlib_library.hpp>
#include <zling_library.hpp>
#include <zpaq_library.hpp>
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
  map_["csc"] = []() { return new CscLibrary(); };
  map_["density"] = []() { return new DensityLibrary(); };
  map_["fari"] = []() { return new FariLibrary(); };
  map_["flz"] = []() { return new FlzLibrary(); };
  map_["gipfeli"] = []() { return new GipfeliLibrary(); };
  map_["heatshrink"] = []() { return new HeatshrinkLibrary(); };
  map_["libbsc"] = []() { return new LibbscLibrary(); };
  map_["libdeflate"] = []() { return new LibdeflateLibrary(); };
  map_["liblzg"] = []() { return new LiblzgLibrary(); };
  map_["lz4"] = []() { return new Lz4Library(); };
  map_["lzf"] = []() { return new LzfLibrary(); };
  map_["lzfse"] = []() { return new LzfseLibrary(); };
  map_["lzfx"] = []() { return new LzfxLibrary(); };
  map_["lzham"] = []() { return new LzhamLibrary(); };
  map_["lzjb"] = []() { return new LzjbLibrary(); };
  map_["lzma"] = []() { return new LzmaLibrary(); };
  map_["lzo"] = []() { return new LzoLibrary(); };
  map_["miniz"] = []() { return new MinizLibrary(); };
  map_["ms"] = []() { return new MsLibrary(); };
  map_["quicklz"] = []() { return new QuicklzLibrary(); };
  map_["snappy"] = []() { return new SnappyLibrary(); };
  map_["wflz"] = []() { return new WflzLibrary(); };
  map_["xpack"] = []() { return new XpackLibrary(); };
  map_["yalz77"] = []() { return new Yalz77Library(); };
  map_["z3lib"] = []() { return new Z3libLibrary(); };
  map_["zlib"] = []() { return new ZlibLibrary(); };
  map_["zlib-ng"] = []() { return new ZlibNgLibrary(); };
  map_["zling"] = []() { return new ZlingLibrary(); };
  map_["zpaq"] = []() { return new ZpaqLibrary(); };
  map_["zstd"] = []() { return new ZstdLibrary(); };
}

CompressionLibraries::~CompressionLibraries() {}
