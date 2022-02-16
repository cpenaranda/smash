cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${SNAPPY_VERSION} snappy)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SNAPPY_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/snappy/snappy-c.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/snappy/snappy-sinksource.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/snappy/snappy-stubs-internal.cc"
  "${CMAKE_CURRENT_SOURCE_DIR}/snappy/snappy.cc"
)
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/snappy
)
add_library(snappy STATIC ${SNAPPY_SOURCES})