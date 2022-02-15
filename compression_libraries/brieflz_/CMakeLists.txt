cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${BRIEFLZ_VERSION} brieflz)

add_subdirectory(brieflz EXCLUDE_FROM_ALL)