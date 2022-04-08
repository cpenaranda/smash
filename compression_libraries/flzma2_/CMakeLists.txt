cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

enable_language( C CXX ASM )

SET(FLZMA2_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2/range_enc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2/fl2_pool.c
  ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2/radix_struct.c
  ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2/lzma2_dec.c
  ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2/xxhash.c
  ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2/fl2_compress.c
  ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2/lzma2_enc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2/fl2_decompress.c
  ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2/radix_bitpack.c
  ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2/fl2_threading.c
  ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2/util.c
  ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2/fl2_common.c
  ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2/dict_buffer.c
  ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2/radix_mf.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2
)

if(CMAKE_SYSTEM_PROCESSOR STREQUAL x86_64)
  SET(FLZMA2_SOURCES
    ${FLZMA2_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2/lzma_dec_x86_64.S
  )
  add_definitions(-DLZMA2_DEC_OPT "-DMS_x64_CALL=0")
endif()

add_library(flzma2 STATIC ${FLZMA2_SOURCES})