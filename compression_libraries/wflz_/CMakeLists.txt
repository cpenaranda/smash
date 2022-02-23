cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${WFLZ_VERSION} wflz)

SET(WFLZ_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/wflz/wfLZ.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/wflz
)

add_library(wflz STATIC ${WFLZ_SOURCES})