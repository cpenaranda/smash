cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

SET(BUILD_SHARED_LIBS OFF)
SET(BUILD_STATIC_LIBS ON)

add_subdirectory(lz4/build/cmake EXCLUDE_FROM_ALL)