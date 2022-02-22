cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/quicklz)
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/quicklz)
endif()

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/quicklz/quicklz.h)
  execute_process(
    COMMAND wget -U "Any" ${QUICKLZ_URL}/quicklz.h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/quicklz
  )
endif()

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/quicklz/quicklz.c)
  execute_process(
    COMMAND wget -U "Any" ${QUICKLZ_URL}/quicklz.c
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/quicklz
  )
endif()

SET(QUICKLZ_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/quicklz/quicklz.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/quicklz
)

add_library(quicklz STATIC ${QUICKLZ_SOURCES})