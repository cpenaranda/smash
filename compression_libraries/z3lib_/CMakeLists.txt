cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository_from_tar(${Z3LIB_URL} z3lib)

SET(Z3LIB_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/z3lib/z3blib.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/z3lib
)
add_library(z3lib STATIC ${Z3LIB_SOURCES})