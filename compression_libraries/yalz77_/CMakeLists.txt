cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${YALZ77_VERSION} yalz77)

SET(YALZ77_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/yalz77/yalz.cc
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/yalz77
)

add_library(yalz77 STATIC ${YALZ77_SOURCES})