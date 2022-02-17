cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${ZLIB_VERSION} zlib)

add_subdirectory(zlib EXCLUDE_FROM_ALL)