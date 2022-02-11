cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${DENSITY_VERSION} density)

set(DENSITY_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/globals.c
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/buffers/buffer.c
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/dictionaries.c
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/algorithms.c
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/lion/core/lion_decode.c
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/lion/core/lion_encode.c
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/lion/forms/lion_form_model.c
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/chameleon/core/chameleon_decode.c
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/chameleon/core/chameleon_encode.c
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/cheetah/core/cheetah_encode.c
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/cheetah/core/cheetah_decode.c
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/structure/header.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/buffers/
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/lion/core/
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/lion/core/
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/lion/forms/
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/chameleon/core/
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/chameleon/core/
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/cheetah/core/
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/cheetah/core/
  ${CMAKE_CURRENT_SOURCE_DIR}/density/src/structure/
)

add_library(density STATIC ${DENSITY_SOURCES})