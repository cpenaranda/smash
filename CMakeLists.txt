cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(TARGET_NAME SMASH)

project(${TARGET_NAME} DESCRIPTION "Smash: Compresion Abstraction Library")

# Set the debug or relese mode.
if (CMAKE_BUILD_TYPE MATCHES Debug) # Debug level
  # Defines
  add_definitions(-DDEBUG)

  # Flags
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
  if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wextra -Wundef")
  endif(CMAKE_COMPILER_IS_GNUCXX)
elseif (CMAKE_BUILD_TYPE MATCHES Release) # Optimization level
else ()
  message(FATAL_ERROR "Set the build type with -DCMAKE_BUILD_TYPE=<type>")
endif()

# Check and add the C++ version.
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++20" COMPILER_SUPPORTS_CXX20)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX20)
  set(CMAKE_CXX_STANDARD 20)
elseif(COMPILER_SUPPORTS_CXX17)
  set(CMAKE_CXX_STANDARD 17)
elseif(COMPILER_SUPPORTS_CXX14)
  set(CMAKE_CXX_STANDARD 14)
elseif(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_STANDARD 11)
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_STANDARD 0X)
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++0x support. Please use a different C++ compiler.")
endif()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(Git REQUIRED)

set (git_update_submodule "${GIT_EXECUTABLE} submodule update --init --recursive --remote")

execute_process(
  COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive --remote
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

function(update_repository VERSION_LIBRARY LIBRARY_NAME)
  if (VERSION_LIBRARY MATCHES "last_tag")
    execute_process(
      COMMAND ${GIT_EXECUTABLE} checkout $(${GIT_EXECUTABLE} describe --tags `git rev-list --tags --max-count=1`)
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY_NAME}
    )
  else()
    execute_process(
      COMMAND ${GIT_EXECUTABLE} checkout ${VERSION_LIBRARY}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY_NAME}
    )
  endif()
endfunction()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(compression_libraries)
add_subdirectory(smash_benchmark)
