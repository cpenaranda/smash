cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(TARGET_NAME smash_benchmark)
project(${TARGET_NAME} DESCRIPTION "Smash benchmark")

include_directories(
  ${smash_library_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${TARGET_NAME} src/smash_benchmark.cpp
                              src/result.cpp
                              src/utils.cpp
)
target_link_libraries(${TARGET_NAME} smash_library)
