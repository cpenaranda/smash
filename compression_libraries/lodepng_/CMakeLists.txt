cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${LODEPNG_VERSION} lodepng)

set(LODEPNG_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/lodepng/lodepng_util.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lodepng/lodepng.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/lodepng/pngdetail.cpp
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/lodepng
)

add_library(lodepng STATIC ${LODEPNG_SOURCES})