cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${FSE_VERSION} FiniteStateEntropy)

SET(FSE_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/entropy_common.c
  ${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/fse_compress.c
  ${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/fse_decompress.c
  ${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/huf_compress.c
  ${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/huf_decompress.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib
)

add_library(fse STATIC ${FSE_SOURCES})