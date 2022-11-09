cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

add_subdirectory(zlib EXCLUDE_FROM_ALL)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/zlib/
  COMMAND ${CMAKE_COMMAND} -E copy zconf.h.in zconf.h
)