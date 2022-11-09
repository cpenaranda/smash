cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

SET(LZF_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzf/lzf_c_best.c
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzf/lzf_c.c
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzf/lzf_d.c
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzf/lzf.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzf
)

add_library(lzf STATIC ${LZF_SOURCES})