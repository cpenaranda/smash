
set(BRIEFLZ_VERSION "v1.3.0")
set(BROTLI_VERSION "v1.0.9")
set(BZIP2_VERSION "bzip2-1.0.8")

add_subdirectory(brieflz_)
add_subdirectory(brotli_)
add_subdirectory(bzip2_)

set(SMASH_LIBRARIES
  brieflz
  brotlidec-static
  brotlienc-static
  bzip2
)

set(SMASH_INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/brieflz/include
  ${CMAKE_CURRENT_SOURCE_DIR}/brotli_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/brotli_/brotli/c/include
  ${CMAKE_CURRENT_SOURCE_DIR}/bzip2_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/bzip2_/bzip2
)

set(SMASH_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/src/brieflz_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/brotli_/src/brotli_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/bzip2_/src/bzip2_library.cpp
)
