cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

SET(QUICKLZ_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/quicklz/quicklz.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/quicklz
)

add_library(quicklz STATIC ${QUICKLZ_SOURCES})