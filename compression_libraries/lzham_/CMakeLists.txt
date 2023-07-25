cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(BUILD_SHARED_LIBS OFF)

add_compile_options(-Wno-int-in-bool-context -Wno-class-memaccess -Wno-maybe-uninitialized)

add_subdirectory(lzham_codec_devel EXCLUDE_FROM_ALL)