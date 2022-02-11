
set(BRIEFLZ_VERSION "v1.3.0")

add_subdirectory(brieflz_)

set(SMASH_LIBRARIES
  brieflz
)

set(SMASH_INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/include
  ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/brieflz/include
)

set(SMASH_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/src/brieflz_library.cpp
)