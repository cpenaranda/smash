cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

file(GLOB GIPFELI_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/gipfeli/*.cc")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/gipfeli
)

add_library(gipfeli STATIC ${GIPFELI_SOURCES})