cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(FLZ_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/fastlz/fastlz.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/fastlz
)

add_library(flz STATIC ${FLZ_SOURCES})