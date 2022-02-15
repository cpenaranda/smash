
set(BRIEFLZ_VERSION "v1.3.0")
set(BROTLI_VERSION "v1.0.9")
set(BZIP2_VERSION "bzip2-1.0.8")
set(CBLOSC2_VERSION "v2.0.4")
set(DENSITY_VERSION "density-0.14.2")
set(LIBDEFLATE_VERSION "v1.9")
set(LZFSE_VERSION "lzfse-1.0")
set(LZMA_VERSION "v5.3.2alpha")

add_subdirectory(brieflz_)
add_subdirectory(brotli_)
add_subdirectory(bzip2_)
add_subdirectory(c-blosc2_)
add_subdirectory(density_)
add_subdirectory(libdeflate_)
add_subdirectory(lzfse_)
add_subdirectory(lzma_)

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
)
