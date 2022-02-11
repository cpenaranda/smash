
set(BRIEFLZ_VERSION "v1.3.0")
set(BROTLI_VERSION "v1.0.9")
set(BZIP2_VERSION "bzip2-1.0.8")
set(CBLOSC2_VERSION "v2.0.4")

add_subdirectory(brieflz_)
add_subdirectory(brotli_)
add_subdirectory(bzip2_)
add_subdirectory(c-blosc2_)

set(SMASH_LIBRARIES
  brieflz
  brotlidec-static
  brotlienc-static
  bzip2
  blosc2_static
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
)

set(SMASH_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/src/brieflz_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/brotli_/src/brotli_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/bzip2_/src/bzip2_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/c-blosc2_/src/c-blosc2_library.cpp
)
