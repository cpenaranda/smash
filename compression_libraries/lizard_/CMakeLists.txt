cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${LIZARD_VERSION} lizard)

file(GLOB LIZARD_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/xxhash/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/entropy/*.c
)

file(GLOB FSE_SOURCES_TO_REPLACE
  ${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/entropy/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/entropy/*.c
)

foreach(FILE_TO_UPDATE IN LISTS FSE_SOURCES_TO_REPLACE)
  replace_all_occurrences(${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/entropy/ ${FILE_TO_UPDATE} "FSE_" "FSE_LIZARD_")
  replace_all_occurrences(${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/entropy/ ${FILE_TO_UPDATE} "HUF_" "HUF_LIZARD_")
endforeach()

replace_all_occurrences(${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/entropy/ mem.h "MEM_H_MODULE"  "MEM_H_MODULE_LIZARD")
replace_all_occurrences(${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/entropy/ error_private.h "ERROR_H_MODULE"  "ERROR_H_MODULE_LIZARD")
replace_all_occurrences(${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/entropy/ bitstream.h "BITSTREAM_H_MODULE"  "BITSTREAM_H_MODULE_LIZARD")
replace_all_occurrences(${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/entropy/ fse.h "FSE_H"  "FSE_H_LIZARD")
replace_all_occurrences(${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/entropy/ huf.h "HUF_H_298734234"  "HUF_H_298734234_LIZARD")
replace_all_occurrences(${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib/entropy/ error_public.h "ERROR_PUBLIC_H_MODULE"  "ERROR_PUBLIC_H_MODULE_LIZARD")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/lizard/lib
)

add_library(lizard STATIC ${LIZARD_SOURCES})