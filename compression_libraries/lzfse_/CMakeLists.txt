cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${LZFSE_VERSION} lzfse)

SET(BUILD_SHARED_LIBS OFF)

add_subdirectory(lzfse)