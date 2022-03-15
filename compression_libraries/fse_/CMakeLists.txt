cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${FSE_VERSION} FiniteStateEntropy)

SET(FSE_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/entropy_common.c
  ${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/fse_compress.c
  ${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/fse_decompress.c
  ${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/huf_compress.c
  ${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/huf_decompress.c
)

file(GLOB FSE_SOURCES_TO_REPLACE
  ${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/*.c
)

foreach(FILE_TO_UPDATE IN LISTS FSE_SOURCES_TO_REPLACE)
  replace_all_occurrences(${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/ ${FILE_TO_UPDATE} "FSE_" "FSE_original_")
  replace_all_occurrences(${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/ ${FILE_TO_UPDATE} "HUF_" "HUF_original_")
endforeach()

replace_all_occurrences(${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/ mem.h "MEM_H_MODULE"  "MEM_H_MODULE_FSE")
replace_all_occurrences(${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/ error_private.h "ERROR_H_MODULE"  "ERROR_H_MODULE_FSE")
replace_all_occurrences(${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/ bitstream.h "BITSTREAM_H_MODULE"  "BITSTREAM_H_MODULE_FSE")
replace_all_occurrences(${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/ fse.h "FSE_H"  "FSE_H_FSE")
replace_all_occurrences(${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/ huf.h "HUF_H_298734234"  "HUF_H_298734234_FSE")
replace_all_occurrences(${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/ error_public.h "ERROR_PUBLIC_H_MODULE"  "ERROR_PUBLIC_H_MODULE_FSE")

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/
  COMMAND sed -i "s+ if ( (size_t)(op-ostart) >= srcSize-1 )+/*if ( (size_t)(op-ostart) >= srcSize-1 )+g" fse_compress.c
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/
  COMMAND sed -i "s+ return op-ostart;+*/return op-ostart;+g" fse_compress.c
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib/
  COMMAND sed -i "s+ if (errorCode == 1) return 0;+//if (errorCode == 1) return 0;+g" fse_compress.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/FiniteStateEntropy/lib
)

add_library(fse STATIC ${FSE_SOURCES})