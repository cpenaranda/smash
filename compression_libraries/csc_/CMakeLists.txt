cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${CSC_VERSION} CSC)

SET(CSC_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/CSC/src/libcsc/csc_analyzer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CSC/src/libcsc/csc_encoder_main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CSC/src/libcsc/csc_coder.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CSC/src/libcsc/csc_filters.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CSC/src/libcsc/csc_lz.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CSC/src/libcsc/csc_memio.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CSC/src/libcsc/csc_enc.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CSC/src/libcsc/csc_dec.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CSC/src/libcsc/csc_model.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CSC/src/libcsc/csc_profiler.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CSC/src/libcsc/csc_mf.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CSC/src/libcsc/csc_default_alloc.cpp
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/CSC/src/libcsc
)

add_definitions(-D_7Z_TYPES_)

add_library(csc STATIC ${CSC_SOURCES})
