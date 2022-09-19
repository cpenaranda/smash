cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

file(GLOB MS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/ms-compress/src/*.cpp")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/ms-compress/include/mscomp
  ${CMAKE_CURRENT_SOURCE_DIR}/ms-compress/include
)

add_library(ms STATIC ${MS_SOURCES})