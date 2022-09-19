cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(LIBDEFLATE_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate/lib/deflate_decompress.c
  ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate/lib/utils.c
  ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate/lib/arm/cpu_features.c
  ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate/lib/x86/cpu_features.c
  ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate/lib/deflate_compress.c
  ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate/lib/adler32.c
  ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate/lib/zlib_decompress.c
  ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate/lib/zlib_compress.c
  ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate/lib/crc32.c
  ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate/lib/gzip_decompress.c
  ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate/lib/gzip_compress.c
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate
)

add_library(libdeflate STATIC ${LIBDEFLATE_SOURCES})