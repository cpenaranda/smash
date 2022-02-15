cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${LZMA_VERSION} xz)

add_subdirectory(xz EXCLUDE_FROM_ALL)