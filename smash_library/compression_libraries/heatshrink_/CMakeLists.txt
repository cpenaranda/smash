cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

SET(HEATSHRINK_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/heatshrink/heatshrink_decoder.c
  ${CMAKE_CURRENT_SOURCE_DIR}/heatshrink/heatshrink_encoder.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/heatshrink
)

add_library(heatshrink STATIC ${HEATSHRINK_SOURCES})