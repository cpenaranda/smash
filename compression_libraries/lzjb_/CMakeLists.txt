cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

SET(LZJB_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/lzjb/lzjb.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/lzjb
)

add_library(lzjb STATIC ${LZJB_SOURCES})