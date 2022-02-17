cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${CBLOSC2_VERSION} c-blosc2)


SET(DEACTIVATE_ZLIB ON)
SET(DEACTIVATE_ZSTD ON)

add_subdirectory(c-blosc2 EXCLUDE_FROM_ALL)