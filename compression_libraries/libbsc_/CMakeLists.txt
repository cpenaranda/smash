cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${LIBBSC_VERSION} libbsc)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libbsc/libbsc
  COMMAND sed -i "s/bsc_init_full(int features, void.* (.* malloc)(size_t size), void.* (.* zero_malloc)(size_t size), void (.* free)(void.* address))/bsc_init_full(int features)/" libbsc.h
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libbsc/libbsc/libbsc
  COMMAND sed -i "s/bsc_init_full(int features, void.* (.* malloc)(size_t size), void.* (.* zero_malloc)(size_t size), void (.* free)(void.* address))/bsc_init_full(int features)/" libbsc.cpp
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libbsc/libbsc/libbsc
  COMMAND sed -i "s/bsc_platform_init(features, malloc, zero_malloc, free);/bsc_platform_init(features, NULL, NULL, NULL);/" libbsc.cpp
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libbsc/libbsc/libbsc
  COMMAND sed -i "s/bsc_init_full(features, NULL, NULL, NULL);/bsc_init_full(features);/" libbsc.cpp
)


SET(LIBBSC_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/libbsc/libbsc/adler32/adler32.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libbsc/libbsc/bwt/libsais/libsais.c
  ${CMAKE_CURRENT_SOURCE_DIR}/libbsc/libbsc/bwt/bwt.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libbsc/libbsc/coder/coder.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libbsc/libbsc/coder/qlfc/qlfc.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libbsc/libbsc/coder/qlfc/qlfc_model.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libbsc/libbsc/filters/detectors.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libbsc/libbsc/filters/preprocessing.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libbsc/libbsc/libbsc/libbsc.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libbsc/libbsc/lzp/lzp.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libbsc/libbsc/platform/platform.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/libbsc/libbsc/st/st.cpp
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/libbsc
)

add_definitions(-DLIBBSC_SORT_TRANSFORM_SUPPORT)

add_library(libbsc STATIC ${LIBBSC_SOURCES})