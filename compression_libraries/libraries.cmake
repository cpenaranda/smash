
set(BRIEFLZ_VERSION "v1.3.0")
set(BROTLI_VERSION "v1.0.9")
set(BZIP2_VERSION "bzip2-1.0.8")
set(CBLOSC2_VERSION "v2.0.4")
set(DENSITY_VERSION "density-0.14.2")
set(LIBDEFLATE_VERSION "v1.9")
set(LZFSE_VERSION "lzfse-1.0")
set(LZMA_VERSION "v5.3.2alpha")
set(LZO_VERSION "master")
set(MS_VERSION "master")
set(SNAPPY_VERSION "1.1.9")
set(XPACK_VERSION "v0.1")
set(ZLIB_VERSION "v1.2.11")
set(ZLIBNG_VERSION "2.0.2")
set(ZSTD_VERSION "v1.5.2")
set(FARI_VERSION "main")
set(FLZ_VERSION "master")
set(GIPFELI_VERSION "master")
set(LZF_VERSION "master")
set(LZJB_VERSION "master")
set(WFLZ_VERSION "master")
set(YALZ77_VERSION "master")
set(ZPAQ_VERSION "7.15")
set(LZHAM_VERSION "master")
set(LIBBSC_VERSION "v3.2.4")
set(HEATSHRINK_VERSION "v0.4.1")
set(ZLING_VERSION "20160108")
set(CSC_VERSION "master")
set(LZ4_VERSION "v1.9.3")
set(MINIZ_VERSION "2.2.0")
set(LIBLZG_VERSION "master")
set(FSE_VERSION "master")
set(LODEPNG_VERSION "master")
set(FLZMA2_VERSION "v1.0.1")
set(LIZARD_VERSION "v1.0")
set(LZSSE_VERSION "master")
set(PITHY_VERSION "master")
set(LZMAT_VERSION "master")

set(LZFX_URL "https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/lzfx/lzfx-0.1.tar.gz")
set(QUICKLZ_URL "https://quicklz.com/")
set(Z3LIB_URL "https://scara.com/~schirmer/o/z3lib/z3lib-1.3.tar.gz")
set(UCL_URL "http://www.oberhumer.com/opensource/ucl/download/ucl-1.03.tar.gz")

add_subdirectory(brieflz_)
add_subdirectory(brotli_)
add_subdirectory(bzip2_)
add_subdirectory(lz4_)
add_subdirectory(c-blosc2_)
add_subdirectory(density_)
add_subdirectory(libdeflate_)
add_subdirectory(lzfse_)
add_subdirectory(lzma_)
add_subdirectory(lzo_)
add_subdirectory(ms_)
add_subdirectory(snappy_)
add_subdirectory(xpack_)
add_subdirectory(zlib_)
add_subdirectory(zlib-ng_)
add_subdirectory(zstd_)
add_subdirectory(lzfx_)
add_subdirectory(fari_)
add_subdirectory(flz_)
add_subdirectory(gipfeli_)
add_subdirectory(lzf_)
add_subdirectory(lzjb_)
add_subdirectory(quicklz_)
add_subdirectory(wflz_)
add_subdirectory(yalz77_)
add_subdirectory(zpaq_)
add_subdirectory(lzham_)
add_subdirectory(z3lib_)
add_subdirectory(libbsc_)
add_subdirectory(heatshrink_)
add_subdirectory(zling_)
add_subdirectory(csc_)
add_subdirectory(miniz_)
add_subdirectory(liblzg_)
add_subdirectory(fse_)
add_subdirectory(ucl_)
add_subdirectory(lodepng_)
add_subdirectory(flzma2_)
add_subdirectory(lizard_)
add_subdirectory(pithy_)
add_subdirectory(lzmat_)

if(CMAKE_SYSTEM_PROCESSOR STREQUAL x86_64)
  add_subdirectory(lzsse_)
endif()

set(SMASH_LIBRARIES
  brieflz
  brotlidec-static
  brotlienc-static
  bzip2
  lz4_static
  blosc2_static
  density
  libdeflate
  lzfse
  liblzma
  lzo_static_lib
  ms
  snappy
  xpack
  zlibstatic
  ng_zlib
  libzstd_static
  lzfx
  fari
  flz
  gipfeli
  lzf
  lzjb
  quicklz
  wflz
  yalz77
  zpaq
  lzhamdll
  z3lib
  libbsc
  heatshrink
  zling
  csc
  miniz
  liblzg
  fse
  ucl
  lodepng
  flzma2
  lizard
  pithy
  lzmat
)

if(CMAKE_SYSTEM_PROCESSOR STREQUAL x86_64)
  set(SMASH_LIBRARIES
    ${SMASH_LIBRARIES}
    lzsse
  )
endif()

set(SMASH_INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/brieflz/include
  ${CMAKE_CURRENT_SOURCE_DIR}/brotli_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/brotli_/brotli/c/include
  ${CMAKE_CURRENT_SOURCE_DIR}/bzip2_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/bzip2_/bzip2
  ${CMAKE_CURRENT_SOURCE_DIR}/lz4_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/lz4_
  ${CMAKE_CURRENT_SOURCE_DIR}/c-blosc2_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/c-blosc2_/c-blosc2/include
  ${CMAKE_CURRENT_SOURCE_DIR}/density_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/density_/density/src
  ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate_/libdeflate
  ${CMAKE_CURRENT_SOURCE_DIR}/lzfse_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/lzfse_/lzfse/src
  ${CMAKE_CURRENT_SOURCE_DIR}/lzma_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/lzma_/xz/src/liblzma/api
  ${CMAKE_CURRENT_SOURCE_DIR}/lzo_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/lzo_/lzo/include
  ${CMAKE_CURRENT_SOURCE_DIR}/ms_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/ms_/ms-compress/include
  ${CMAKE_CURRENT_SOURCE_DIR}/ms_/ms-compress/include/mscomp
  ${CMAKE_CURRENT_SOURCE_DIR}/snappy_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/snappy_/snappy
  ${CMAKE_CURRENT_SOURCE_DIR}/xpack_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/xpack_/xpack
  ${CMAKE_CURRENT_SOURCE_DIR}/zlib_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/zlib_/zlib
  ${CMAKE_CURRENT_SOURCE_DIR}/zlib-ng_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/zlib-ng_/zlib-ng
  ${CMAKE_CURRENT_SOURCE_DIR}/zstd_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/zstd_/zstd/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/lzfx_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/lzfx_/lzfx
  ${CMAKE_CURRENT_SOURCE_DIR}/fari_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/fari_/FastARI
  ${CMAKE_CURRENT_SOURCE_DIR}/flz_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/flz_/fastlz
  ${CMAKE_CURRENT_SOURCE_DIR}/gipfeli_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/gipfeli_/gipfeli
  ${CMAKE_CURRENT_SOURCE_DIR}/lzf_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/lzf_/liblzf
  ${CMAKE_CURRENT_SOURCE_DIR}/lzjb_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/lzjb_/lzjb
  ${CMAKE_CURRENT_SOURCE_DIR}/quicklz_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/quicklz_/quicklz
  ${CMAKE_CURRENT_SOURCE_DIR}/wflz_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/wflz_/wflz
  ${CMAKE_CURRENT_SOURCE_DIR}/yalz77_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/yalz77_/
  ${CMAKE_CURRENT_SOURCE_DIR}/zpaq_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/zpaq_/zpaq
  ${CMAKE_CURRENT_SOURCE_DIR}/lzham_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/lzham_/lzham_codec_devel/include
  ${CMAKE_CURRENT_SOURCE_DIR}/lzham_/lzham_codec_devel/lzhamcomp
  ${CMAKE_CURRENT_SOURCE_DIR}/lzham_/lzham_codec_devel/lzhamdecomp
  ${CMAKE_CURRENT_SOURCE_DIR}/z3lib_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/z3lib_/z3lib
  ${CMAKE_CURRENT_SOURCE_DIR}/libbsc_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/libbsc_/libbsc
  ${CMAKE_CURRENT_SOURCE_DIR}/heatshrink_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/heatshrink_/heatshrink
  ${CMAKE_CURRENT_SOURCE_DIR}/zling_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/zling_/libzling/src
  ${CMAKE_CURRENT_SOURCE_DIR}/csc_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/csc_/CSC/src/libcsc
  ${CMAKE_CURRENT_SOURCE_DIR}/miniz_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/miniz_/miniz
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzg_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzg_/liblzg/src/include
  ${CMAKE_CURRENT_SOURCE_DIR}/fse_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/fse_/FiniteStateEntropy/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/ucl_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/ucl_/ucl/include
  ${CMAKE_CURRENT_SOURCE_DIR}/lodepng_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/lodepng_/lodepng
  ${CMAKE_CURRENT_SOURCE_DIR}/flzma2_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/flzma2_/fast-lzma2
  ${CMAKE_CURRENT_SOURCE_DIR}/lizard_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/lizard_/lizard/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/pithy_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/pithy_/pithy
  ${CMAKE_CURRENT_SOURCE_DIR}/lzmat_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/lzmat_/lzmat
)

if(CMAKE_SYSTEM_PROCESSOR STREQUAL x86_64)
  set(SMASH_INCLUDES
    ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzsse_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lzsse_/LZSSE/lzsse2
    ${CMAKE_CURRENT_SOURCE_DIR}/lzsse_/LZSSE/lzsse4
    ${CMAKE_CURRENT_SOURCE_DIR}/lzsse_/LZSSE/lzsse8
  )
endif()

set(SMASH_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/src/brieflz_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/brotli_/src/brotli_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/bzip2_/src/bzip2_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/c-blosc2_/src/c-blosc2_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/density_/src/density_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate_/src/libdeflate_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lzfse_/src/lzfse_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lzma_/src/lzma_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lzo_/src/lzo_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ms_/src/ms_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/snappy_/src/snappy_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/xpack_/src/xpack_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/zlib_/src/zlib_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/zlib-ng_/src/zlib-ng_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/zstd_/src/zstd_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lzfx_/src/lzfx_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/fari_/src/fari_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/flz_/src/flz_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/gipfeli_/src/gipfeli_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lzf_/src/lzf_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lzjb_/src/lzjb_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/quicklz_/src/quicklz_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/wflz_/src/wflz_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/yalz77_/src/yalz77_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/zpaq_/src/zpaq_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lzham_/src/lzham_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/z3lib_/src/z3lib_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libbsc_/src/libbsc_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/heatshrink_/src/heatshrink_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/zling_/src/zling_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/csc_/src/csc_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lz4_/src/lz4_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/miniz_/src/miniz_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzg_/src/liblzg_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/fse_/src/fse_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ucl_/src/ucl_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lodepng_/src/lodepng_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/flzma2_/src/flzma2_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lizard_/src/lizard_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/pithy_/src/pithy_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lzmat_/src/lzmat_library.cpp
)

if(CMAKE_SYSTEM_PROCESSOR STREQUAL x86_64)
  set(SMASH_SOURCES
    ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzsse_/src/lzsse_library.cpp
  )
endif()