cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

SET(PITHY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/pithy/pithy.c)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/pithy
)

add_library(pithy STATIC ${PITHY_SOURCES})