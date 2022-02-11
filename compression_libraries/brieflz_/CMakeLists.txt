cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(brieflz_update ${BRIEFLZ_VERSION} brieflz)

add_subdirectory(brieflz)

add_dependencies(brieflz brieflz_update)