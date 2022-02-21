cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository(${LZO_VERSION} lzo)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lzo/
  COMMAND sed -i "s/^lzo_add_executable(simple/#lzo_add_executable(simple/" CMakeLists.txt
)

add_subdirectory(lzo EXCLUDE_FROM_ALL)