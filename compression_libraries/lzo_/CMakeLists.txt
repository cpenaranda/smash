cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${LZO_VERSION} lzo)

file(GLOB LZO_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lzo/src/*.c")
list(SORT LZO_SOURCES)
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/lzo/src
  ${CMAKE_CURRENT_SOURCE_DIR}/lzo/include
)
add_library(lzo STATIC ${LZO_SOURCES})