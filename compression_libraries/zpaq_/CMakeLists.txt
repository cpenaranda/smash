cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

SET(ZPAQ_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/zpaq/libzpaq.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/zpaq/zpaq.cpp
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/zpaq
)

add_library(zpaq STATIC ${ZPAQ_SOURCES})