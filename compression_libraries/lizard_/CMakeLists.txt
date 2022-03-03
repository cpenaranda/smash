cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${LIZARD_VERSION} lizard)

file(GLOB LIZARD_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/xxhash/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/entropy/*.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib
)

add_library(lizard STATIC ${LIZARD_SOURCES})