cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${LIBLZG_VERSION} liblzg)

SET(LIBLZG_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzg/src/lib/encode.c
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzg/src/lib/decode.c
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzg/src/lib/checksum.c
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzg/src/lib/version.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzg/src/lib
)

add_library(liblzg STATIC ${LIBLZG_SOURCES})