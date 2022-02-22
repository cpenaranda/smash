cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${GIPFELI_VERSION} gipfeli)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/gipfeli/
  COMMAND sed -i "s+^ private:+// private:+" gipfeli-internal.h
)

file(GLOB GIPFELI_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/gipfeli/*.cc")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/gipfeli
)

add_library(gipfeli STATIC ${GIPFELI_SOURCES})