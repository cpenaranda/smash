cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${LZHAM_VERSION} lzham)

set(BUILD_SHARED_LIBS OFF)

add_subdirectory(lzham_codec_devel EXCLUDE_FROM_ALL)