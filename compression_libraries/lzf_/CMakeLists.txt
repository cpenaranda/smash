cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${LZF_VERSION} liblzf)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/liblzf/
  COMMAND sed -i "s/const u8 .*b = ip/const u8 *b = (const u8*)(ip/" lzf_c_best.c
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/liblzf/
  COMMAND sed -i "s/ip - LZF_MAX_OFF;/ip - LZF_MAX_OFF);/" lzf_c_best.c
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/liblzf/
  COMMAND sed -i "s+^#include \"config.h\"+// #include \"config.h\"+" lzf.c
)

SET(LZF_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzf/lzf_c_best.c
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzf/lzf_c.c
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzf/lzf_d.c
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzf/lzf.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/liblzf
)

add_library(lzf STATIC ${LZF_SOURCES})