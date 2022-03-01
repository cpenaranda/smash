cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${ZLING_VERSION} zling)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libzling/build/
  COMMAND sed -i "s/SHARED/STATIC/" CMakeLists.txt
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libzling/src/
  COMMAND sed -i "36d" libzling_huffman.cpp
)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libzling/src/
  COMMAND sed -i "36 i #include <functional>" libzling_huffman.cpp
)

add_subdirectory(libzling/build EXCLUDE_FROM_ALL)