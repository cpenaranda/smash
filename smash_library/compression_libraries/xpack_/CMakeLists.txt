cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

file(GLOB XPACK_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/xpack/lib/*.c")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/xpack
  ${CMAKE_CURRENT_SOURCE_DIR}/xpack/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/xpack/common
)

add_library(xpack STATIC ${XPACK_SOURCES})