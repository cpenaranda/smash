cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

SET(LZMAT_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/lzmat/lzmat_enc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/lzmat/lzmat_dec.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/lzmat
)

add_compile_options(-Wno-pointer-to-int-cast)

add_library(lzmat STATIC ${LZMAT_SOURCES})