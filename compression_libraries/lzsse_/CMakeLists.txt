cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${LZSSE_VERSION} LZSSE)

SET(LZSSE_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/LZSSE/lzsse2/lzsse2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/LZSSE/lzsse4/lzsse4.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/LZSSE/lzsse8/lzsse8.cpp
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/LZSSE/lzsse2
  ${CMAKE_CURRENT_SOURCE_DIR}/LZSSE/lzsse4
  ${CMAKE_CURRENT_SOURCE_DIR}/LZSSE/lzsse8
)

add_definitions("-march=native")

add_library(lzsse STATIC ${LZSSE_SOURCES})