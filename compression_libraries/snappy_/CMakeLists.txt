cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

option(SNAPPY_BUILD_TESTS "Build Snappy's own tests." OFF)
option(SNAPPY_BUILD_BENCHMARKS "Build Snappy's benchmarks" OFF)

add_compile_options(-Wno-sign-compare -Wno-attributes)

add_subdirectory(snappy EXCLUDE_FROM_ALL)