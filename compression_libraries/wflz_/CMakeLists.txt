cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

SET(WFLZ_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/wflz/wfLZ.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/wflz
)

add_definitions(-DWF_LZ_NO_UNALIGNED_ACCESS)

add_library(wflz STATIC ${WFLZ_SOURCES})