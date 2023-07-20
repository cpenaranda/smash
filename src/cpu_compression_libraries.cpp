/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <iomanip>
#include <iostream>

// CPU-SMASH LIBRARIES
#ifdef BRIEFLZ
#include <brieflz_library.hpp>
#endif  // BRIEFLZ
#ifdef BROTLI
#include <brotli_library.hpp>
#endif  // BROTLI
#ifdef BZIP2
#include <bzip2_library.hpp>
#endif  // BZIP2
#ifdef CBLOSC2
#include <c-blosc2_library.hpp>
#endif  // CBLOSC2
#include <cpu_compression_libraries.hpp>
#ifdef CSC
#include <csc_library.hpp>
#endif  // CSC
#ifdef DENSITY
#include <density_library.hpp>
#endif  // DENSITY
#ifdef FLZ
#include <flz_library.hpp>
#endif  // FLZ
#ifdef FLZMA2
#include <flzma2_library.hpp>
#endif  // FLZMA2
#ifdef FSE
#include <fse_library.hpp>
#endif  // FSE
#ifdef GIPFELI
#include <gipfeli_library.hpp>
#endif  // GIPFELI
#ifdef HEATSHRINK
#include <heatshrink_library.hpp>
#endif  // HEATSHRINK
#ifdef LIBBSC
#include <libbsc_library.hpp>
#endif  // LIBBSC
#ifdef LIBDEFLATE
#include <libdeflate_library.hpp>
#endif  // LIBDEFLATE
#ifdef LIBLZG
#include <liblzg_library.hpp>
#endif  // LIBLZG
#ifdef LIZARD
#include <lizard_library.hpp>
#endif  // LIZARD
#ifdef LODEPNG
#include <lodepng_library.hpp>
#endif  // LODEPNG
#ifdef LZ4
#include <lz4_library.hpp>
#endif  // LZ4
#ifdef LZF
#include <lzf_library.hpp>
#endif  // LZF
#ifdef LZFSE
#include <lzfse_library.hpp>
#endif  // LZFSE
#ifdef LZFX
#include <lzfx_library.hpp>
#endif  // LZFX
#ifdef LZHAM
#include <lzham_library.hpp>
#endif  // LZHAM
#ifdef LZJB
#include <lzjb_library.hpp>
#endif  // LZJB
#ifdef LZMA
#include <lzma_library.hpp>
#endif  // LZMA
#ifdef LZMAT
#include <lzmat_library.hpp>
#endif  // LZMAT
#ifdef LZO
#include <lzo_library.hpp>
#endif  // LZO
#ifdef MINIZ
#include <miniz_library.hpp>
#endif  // MINIZ
#ifdef MS
#include <ms_library.hpp>
#endif  // MS
#ifdef PITHY
#include <pithy_library.hpp>
#endif  // PITHY
#ifdef QUICKLZ
#include <quicklz_library.hpp>
#endif  // QUICKLZ
#ifdef SNAPPY
#include <snappy_library.hpp>
#endif  // SNAPPY
#ifdef UCL
#include <ucl_library.hpp>
#endif  // UCL
#ifdef WFLZ
#include <wflz_library.hpp>
#endif  // WFLZ
#ifdef XPACK
#include <xpack_library.hpp>
#endif  // XPACK
#ifdef YALZ77
#include <yalz77_library.hpp>
#endif  // YALZ77
#ifdef Z3LIB
#include <z3lib_library.hpp>
#endif  // Z3LIB
#ifdef ZLIB_NG
#include <zlib-ng_library.hpp>
#endif  // ZLIB_NG
#ifdef ZLIB
#include <zlib_library.hpp>
#endif  // ZLIB
#ifdef ZLING
#include <zling_library.hpp>
#endif  // ZLING
#ifdef ZPAQ
#include <zpaq_library.hpp>
#endif  // ZPAQ
#ifdef ZSTD
#include <zstd_library.hpp>
#endif  // ZSTD
#ifdef __x86_64__
#ifdef LZSSE
#include <lzsse_library.hpp>
#endif  // LZSSE
#endif  // __x86_64__

CpuCompressionLibrary *CpuCompressionLibraries::GetCompressionLibrary(
    const std::string &library_name) {
  auto lib = map_.find(library_name);
  if (lib == map_.end()) {
    std::cout << "ERROR: The compression library does not exist" << std::endl;
    exit(EXIT_FAILURE);
  }
  return lib->second();
}

void CpuCompressionLibraries::GetListInformation() {
  CpuCompressionLibrary *library;
  int i = 0;
  for (auto &lib : map_) {
    library = lib.second();
    std::cout << std::right << std::setw(3) << std::setfill(' ') << ++i << ": ";
    library->GetTitle();
    delete library;
  }
}

std::vector<std::string> CpuCompressionLibraries::GetNameLibraries() {
  std::vector<std::string> result;
  for (auto &lib : map_) {
    result.push_back(lib.first);
  }
  return result;
}

CpuCompressionLibraries::CpuCompressionLibraries() {
#ifdef BRIEFLZ
  map_["brieflz"] = []() { return new BrieflzLibrary(); };
#endif  // BRIEFLZ
#ifdef BROTLI
  map_["brotli"] = []() { return new BrotliLibrary(); };
#endif  // BROTLI
#ifdef BZIP2
  map_["bzip2"] = []() { return new Bzip2Library(); };
#endif  // BZIP2
#ifdef CBLOSC2
  map_["c-blosc2"] = []() { return new CBlosc2Library(); };
#endif  // CBLOSC2
#ifdef CSC
  map_["csc"] = []() { return new CscLibrary(); };
#endif  // CSC
#ifdef DENSITY
  map_["density"] = []() { return new DensityLibrary(); };
#endif  // DENSITY
#ifdef FLZ
  map_["flz"] = []() { return new FlzLibrary(); };
#endif  // FLZ
#ifdef FLZMA2
  map_["flzma2"] = []() { return new Flzma2Library(); };
#endif  // FLZMA2
#ifdef FSE
  map_["fse"] = []() { return new FseLibrary(); };
#endif  // FSE
#ifdef GIPFELI
  map_["gipfeli"] = []() { return new GipfeliLibrary(); };
#endif  // GIPFELI
#ifdef HEATSHRINK
  map_["heatshrink"] = []() { return new HeatshrinkLibrary(); };
#endif  // HEATSHRINK
#ifdef LIBBSC
  map_["libbsc"] = []() { return new LibbscLibrary(); };
#endif  // LIBBSC
#ifdef LIBDEFLATE
  map_["libdeflate"] = []() { return new LibdeflateLibrary(); };
#endif  // LIBDEFLATE
#ifdef LIBLZG
  map_["liblzg"] = []() { return new LiblzgLibrary(); };
#endif  // LIBLZG
#ifdef LIZARD
  map_["lizard"] = []() { return new LizardLibrary(); };
#endif  // LIZARD
#ifdef LODEPNG
  map_["lodepng"] = []() { return new LodepngLibrary(); };
#endif  // LODEPNG
#ifdef LZ4
  map_["lz4"] = []() { return new Lz4Library(); };
#endif  // LZ4
#ifdef LZF
  map_["lzf"] = []() { return new LzfLibrary(); };
#endif  // LZF
#ifdef LZFSE
  map_["lzfse"] = []() { return new LzfseLibrary(); };
#endif  // LZFSE
#ifdef LZFX
  map_["lzfx"] = []() { return new LzfxLibrary(); };
#endif  // LZFX
#ifdef LZHAM
  map_["lzham"] = []() { return new LzhamLibrary(); };
#endif  // LZHAM
#ifdef LZJB
  map_["lzjb"] = []() { return new LzjbLibrary(); };
#endif  // LZJB
#ifdef LZMA
  map_["lzma"] = []() { return new LzmaLibrary(); };
#endif  // LZMA
#ifdef LZMAT
  map_["lzmat"] = []() { return new LzmatLibrary(); };
#endif  // LZMAT
#ifdef LZO
  map_["lzo"] = []() { return new LzoLibrary(); };
#endif  // LZO
#ifdef MINIZ
  map_["miniz"] = []() { return new MinizLibrary(); };
#endif  // MINIZ
#ifdef MS
  map_["ms"] = []() { return new MsLibrary(); };
#endif  // MS
#ifdef PITHY
  map_["pithy"] = []() { return new PithyLibrary(); };
#endif  // PITHY
#ifdef QUICKLZ
  map_["quicklz"] = []() { return new QuicklzLibrary(); };
#endif  // QUICKLZ
#ifdef SNAPPY
  map_["snappy"] = []() { return new SnappyLibrary(); };
#endif  // SNAPPY
#ifdef UCL
  map_["ucl"] = []() { return new UclLibrary(); };
#endif  // UCL
#ifdef WFLZ
  map_["wflz"] = []() { return new WflzLibrary(); };
#endif  // WFLZ
#ifdef XPACK
  map_["xpack"] = []() { return new XpackLibrary(); };
#endif  // XPACK
#ifdef YALZ77
  map_["yalz77"] = []() { return new Yalz77Library(); };
#endif  // YALZ77
#ifdef Z3LIB
  map_["z3lib"] = []() { return new Z3libLibrary(); };
#endif  // Z3LIB
#ifdef ZLIB
  map_["zlib"] = []() { return new ZlibLibrary(); };
#endif  // ZLIB
#ifdef ZLIB_NG
  map_["zlib-ng"] = []() { return new ZlibNgLibrary(); };
#endif  // ZLIB_NG
#ifdef ZLING
  map_["zling"] = []() { return new ZlingLibrary(); };
#endif  // ZLING
#ifdef ZPAQ
  map_["zpaq"] = []() { return new ZpaqLibrary(); };
#endif  // ZPAQ
#ifdef ZSTD
  map_["zstd"] = []() { return new ZstdLibrary(); };
#endif  // ZSTD

#ifdef __x86_64__
#ifdef LZSSE
  map_["lzsse"] = []() { return new LzsseLibrary(); };
#endif  // LZSSE
#endif  // __x86_64__
}

CpuCompressionLibraries::~CpuCompressionLibraries() {}
