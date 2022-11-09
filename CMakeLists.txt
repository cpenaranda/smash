cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(TARGET_NAME smash)

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

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(ALLOW_DUPLICATE_CUSTOM_TARGETS TRUE)

include(compression_libraries/libraries.cmake)

set(SMASH_SOURCES
  ${SMASH_SOURCES}
  src/smash.cpp
  src/compression_library.cpp
  src/compression_libraries.cpp
  src/options.cpp
  src/smash_chunks.cpp
  src/smash_connection.cpp
  src/smash_memory.cpp
  src/smash_network.cpp
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${SMASH_INCLUDES}
)

add_library(${TARGET_NAME} STATIC ${SMASH_SOURCES})
target_link_libraries(${TARGET_NAME} ${SMASH_LIBRARIES})
