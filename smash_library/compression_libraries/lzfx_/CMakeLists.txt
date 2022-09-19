cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

file(GLOB LZFX_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lzfx/lzfx.c")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/lzfx
)

add_library(lzfx STATIC ${LZFX_SOURCES})