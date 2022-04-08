cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(FARI_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/FastARI/FastAri.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/FastARI
)

add_definitions(-DFA_USE_EOF)

add_library(fari STATIC ${FARI_SOURCES})