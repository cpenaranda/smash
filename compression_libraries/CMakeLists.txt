cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

include(libraries.cmake)

set(TARGET_NAME smash_library)
project(${TARGET_NAME} DESCRIPTION "Smash library")

set(SMASH_SOURCES
  ${SMASH_SOURCES}
  src/smash.cpp
  src/compression_library.cpp
  src/compression_libraries.cpp
  src/options.cpp
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${SMASH_INCLUDES}
)

add_library(${TARGET_NAME} STATIC ${SMASH_SOURCES})
target_link_libraries(${TARGET_NAME} ${SMASH_LIBRARIES})
