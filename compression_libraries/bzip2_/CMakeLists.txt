cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${BZIP2_VERSION} bzip2)

set(BZIP2_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/bzip2/blocksort.c
  ${CMAKE_CURRENT_SOURCE_DIR}/bzip2/huffman.c
  ${CMAKE_CURRENT_SOURCE_DIR}/bzip2/crctable.c
  ${CMAKE_CURRENT_SOURCE_DIR}/bzip2/randtable.c
  ${CMAKE_CURRENT_SOURCE_DIR}/bzip2/compress.c
  ${CMAKE_CURRENT_SOURCE_DIR}/bzip2/decompress.c
  ${CMAKE_CURRENT_SOURCE_DIR}/bzip2/bzlib.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/bzip2
)

add_library(bzip2 STATIC ${BZIP2_SOURCES})