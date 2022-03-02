cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${MINIZ_VERSION} miniz)

add_subdirectory(miniz EXCLUDE_FROM_ALL)