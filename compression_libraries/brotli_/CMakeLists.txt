cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${BROTLI_VERSION} brotli)

add_subdirectory(brotli EXCLUDE_FROM_ALL)