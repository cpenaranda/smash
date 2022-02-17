cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${ZLIBNG_VERSION} zlib-ng)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/zlib-ng/
  COMMAND sed -i "s/add_library(zlib/add_library(ng_zlib/" CMakeLists.txt
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/zlib-ng/
  COMMAND sed -i "s/ALIAS zlib)/ALIAS ng_zlib)/" CMakeLists.txt
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/zlib-ng/
  COMMAND sed -i "s/set(ZLIB_INSTALL_LIBRARIES zlib)/set(ZLIB_INSTALL_LIBRARIES ng_zlib)/" CMakeLists.txt
)

set(ZLIB_ENABLE_TESTS OFF)
add_subdirectory(zlib-ng EXCLUDE_FROM_ALL)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/zlib-ng/
  COMMAND ${CMAKE_COMMAND} -E copy zconf-ng.h.in zconf-ng.h
)