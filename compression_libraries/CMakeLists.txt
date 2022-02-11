cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

include(libraries.cmake)

set(TARGET_NAME smash_library)
project(${TARGET_NAME} DESCRIPTION "Smash library")



set(SMASH_SOURCES
  src/smash.cpp
  src/compression_library.cpp
  src/compression_libraries.cpp
  src/options.cpp
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(${TARGET_NAME} STATIC ${SMASH_SOURCES})
