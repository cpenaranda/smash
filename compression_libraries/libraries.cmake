
set(BRIEFLZ_VERSION "v1.3.0")
set(BROTLI_VERSION "v1.0.9")

add_subdirectory(brieflz_)
add_subdirectory(brotli_)

set(SMASH_LIBRARIES
  brieflz
  brotlidec-static
  brotlienc-static
)

set(SMASH_INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/brieflz/include
  ${CMAKE_CURRENT_SOURCE_DIR}/brotli_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/brotli_/brotli/c/include
)

set(SMASH_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/src/brieflz_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/brotli_/src/brotli_library.cpp
)
