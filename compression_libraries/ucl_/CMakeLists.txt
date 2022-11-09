cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

file(GLOB UCL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/ucl/src/*c*")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/ucl/src
  ${CMAKE_CURRENT_SOURCE_DIR}/ucl/include
  ${CMAKE_CURRENT_SOURCE_DIR}/ucl
)

add_library(ucl STATIC ${UCL_SOURCES})