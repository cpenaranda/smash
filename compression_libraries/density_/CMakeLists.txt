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

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/lion/core/
  COMMAND sed -i "s+in_size - DENSITY_LION_MAXIMUM_COMPRESSED_UNIT_SIZE+in_size+g" lion_decode.c
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/lion/core/
  COMMAND sed -i "s+ return DENSITY_ALGORITHMS_EXIT_STATUS_OUTPUT_STALL;+//return DENSITY_ALGORITHMS_EXIT_STATUS_OUTPUT_STALL;+g" lion_decode.c
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/lion/core/
  COMMAND sed -i "s+ if (.*out > out_limit)+//if (*out > out_limit)+g" lion_decode.c
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/lion/core/
  COMMAND sed -i "s+ if (out_size < DENSITY_LION_MAXIMUM_DECOMPRESSED_UNIT_SIZE)+//if (out_size < DENSITY_LION_MAXIMUM_DECOMPRESSED_UNIT_SIZE)+g" lion_decode.c
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/cheetah/core/
  COMMAND sed -i "s+in_size - DENSITY_CHEETAH_MAXIMUM_COMPRESSED_UNIT_SIZE+in_size+g" cheetah_decode.c
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/cheetah/core/
  COMMAND sed -i "s+ return DENSITY_ALGORITHMS_EXIT_STATUS_OUTPUT_STALL;+//return DENSITY_ALGORITHMS_EXIT_STATUS_OUTPUT_STALL;+g" cheetah_decode.c
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/cheetah/core/
  COMMAND sed -i "s+ if (out_size < DENSITY_CHEETAH_DECOMPRESSED_UNIT_SIZE)+//if (out_size < DENSITY_CHEETAH_DECOMPRESSED_UNIT_SIZE)+g" cheetah_decode.c
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/cheetah/core/
  COMMAND sed -i "s+ if (.*out > out_limit)+//if (*out > out_limit)+g" cheetah_decode.c
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/chameleon/core/
  COMMAND sed -i "s+in_size - DENSITY_CHAMELEON_MAXIMUM_COMPRESSED_UNIT_SIZE+in_size+g" chameleon_decode.c
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/chameleon/core/
  COMMAND sed -i "s+ return DENSITY_ALGORITHMS_EXIT_STATUS_OUTPUT_STALL;+//return DENSITY_ALGORITHMS_EXIT_STATUS_OUTPUT_STALL;+g" chameleon_decode.c
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/chameleon/core/
  COMMAND sed -i "s+ if (out_size < DENSITY_CHAMELEON_DECOMPRESSED_UNIT_SIZE)+//if (out_size < DENSITY_CHAMELEON_DECOMPRESSED_UNIT_SIZE)+g" chameleon_decode.c
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/density/src/algorithms/chameleon/core/
  COMMAND sed -i "s+ if (.*out > out_limit)+//if (*out > out_limit)+g" chameleon_decode.c
)

add_library(density STATIC ${DENSITY_SOURCES})