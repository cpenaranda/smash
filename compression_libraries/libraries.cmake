
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


set(LZFX_URL "https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/lzfx/lzfx-0.1.tar.gz")

add_subdirectory(brieflz_)
add_subdirectory(brotli_)
add_subdirectory(bzip2_)
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

set(SMASH_LIBRARIES
  brieflz
  brotlidec-static
  brotlienc-static
  bzip2
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
)

set(SMASH_INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/brieflz/include
  ${CMAKE_CURRENT_SOURCE_DIR}/brotli_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/brotli_/brotli/c/include
  ${CMAKE_CURRENT_SOURCE_DIR}/bzip2_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/bzip2_/bzip2
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
  ${CMAKE_CURRENT_SOURCE_DIR}/lzo_/lzo/include/lzo
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
)

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
)
