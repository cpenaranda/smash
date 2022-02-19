cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${ZSTD_VERSION} zstd)

add_subdirectory(zstd/build/cmake EXCLUDE_FROM_ALL)
