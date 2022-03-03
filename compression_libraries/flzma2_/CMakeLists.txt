cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

enable_language( C CXX ASM )

update_repository(${FLZMA2_VERSION} fast-lzma2)

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
  ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2/lzma_dec_x86_64.S
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/fast-lzma2
)

add_definitions(-DLZMA2_DEC_OPT "-DMS_x64_CALL=0")

add_library(flzma2 STATIC ${FLZMA2_SOURCES})