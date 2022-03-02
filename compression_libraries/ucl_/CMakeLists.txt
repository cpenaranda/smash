cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

update_repository_from_tar(${UCL_URL} ucl)

execute_process(
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ucl/acc/
  COMMAND sed -i "s/define ACC_COMPILE_TIME_ASSERT_HEADER(e) .*/define ACC_COMPILE_TIME_ASSERT_HEADER(e)/" acc_defs.h
)

file(GLOB UCL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/ucl/src/*c*")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/ucl/src
  ${CMAKE_CURRENT_SOURCE_DIR}/ucl/include
  ${CMAKE_CURRENT_SOURCE_DIR}/ucl
)

add_library(ucl STATIC ${UCL_SOURCES})