cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(ZLIB_ENABLE_TESTS OFF)

add_subdirectory(zlib-ng EXCLUDE_FROM_ALL)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/zlib-ng/
  COMMAND ${CMAKE_COMMAND} -E copy zconf-ng.h.in zconf-ng.h
)