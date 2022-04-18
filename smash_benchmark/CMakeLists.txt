cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(TARGET_NAME smash_benchmark)
project(${TARGET_NAME} DESCRIPTION "Smash benchmark")

include_directories(
  ${smash_library_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${TARGET_NAME} src/smash_benchmark.cpp
                              src/result.cpp
                              src/utils.cpp
)
target_link_libraries(${TARGET_NAME} smash_library)

add_executable(${TARGET_NAME}_client src/smash_benchmark_client.cpp
                                     src/result.cpp
                                     src/utils.cpp
                                     src/network.cpp
                                     src/network_client.cpp
)

target_link_libraries(${TARGET_NAME}_client smash_library)

add_executable(${TARGET_NAME}_server src/smash_benchmark_server.cpp
                                     src/result.cpp
                                     src/utils.cpp
                                     src/network.cpp
                                     src/network_server.cpp
)

target_link_libraries(${TARGET_NAME}_server smash_library)
