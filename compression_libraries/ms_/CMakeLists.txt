cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${MS_VERSION} ms-compress)

file(GLOB MS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/ms-compress/src/*.cpp")
list(SORT MS_SOURCES)
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/ms-compress/include/mscomp
  ${CMAKE_CURRENT_SOURCE_DIR}/ms-compress/include
)

add_library(ms STATIC ${MS_SOURCES})