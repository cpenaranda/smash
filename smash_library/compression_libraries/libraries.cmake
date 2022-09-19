if (NOT BRIEFLZ MATCHES OFF)
  add_subdirectory(compression_libraries/brieflz_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} brieflz)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
      ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/brieflz_/include
      ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/brieflz_/brieflz/include
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
      ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/brieflz_/src/brieflz_library.cpp
  )
  add_definitions(-DBRIEFLZ)
endif()

if (NOT BROTLI MATCHES OFF)
  add_subdirectory(compression_libraries/brotli_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} brotlidec-static brotlienc-static)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/brotli_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/brotli_/brotli/c/include
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/brotli_/src/brotli_library.cpp
  )
  add_definitions(-DBROTLI)
endif()

if (NOT BZIP2 MATCHES OFF)
  add_subdirectory(compression_libraries/bzip2_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} bzip2)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/bzip2_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/bzip2_/bzip2
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/bzip2_/src/bzip2_library.cpp
  )
  add_definitions(-DBZIP2)
endif()

if (NOT LZ4 MATCHES OFF)
  add_subdirectory(compression_libraries/lz4_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lz4_static)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lz4_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lz4_
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lz4_/src/lz4_library.cpp
  )
  add_definitions(-DLZ4)
endif()

if (NOT CBLOSC2 MATCHES OFF)
  add_subdirectory(compression_libraries/c-blosc2_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} blosc2_static)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/c-blosc2_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/c-blosc2_/c-blosc2/include
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/c-blosc2_/src/c-blosc2_library.cpp
  )
  add_definitions(-DCBLOSC2)
endif()

if (NOT DENSITY MATCHES OFF)
  add_subdirectory(compression_libraries/density_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} density)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/density_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/density_/density/src
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/density_/src/density_library.cpp
  )
  add_definitions(-DDENSITY)
endif()

if (NOT LIBDEFLATE MATCHES OFF)
  add_subdirectory(compression_libraries/libdeflate_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} libdeflate)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/libdeflate_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/libdeflate_/libdeflate
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/libdeflate_/src/libdeflate_library.cpp
  )
  add_definitions(-DLIBDEFLATE)
endif()

if (NOT LZFSE MATCHES OFF)
  add_subdirectory(compression_libraries/lzfse_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lzfse)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzfse_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzfse_/lzfse/src
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzfse_/src/lzfse_library.cpp
  )
  add_definitions(-DLZFSE)
endif()

if (NOT LZMA MATCHES OFF)
  add_subdirectory(compression_libraries/lzma_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} liblzma)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzma_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzma_/xz/src/liblzma/api
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzma_/src/lzma_library.cpp
  )
  add_definitions(-DLZMA)
endif()

if (NOT LZO MATCHES OFF)
  add_subdirectory(compression_libraries/lzo_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lzo_static_lib)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzo_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzo_/lzo/include
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzo_/src/lzo_library.cpp
  )
  add_definitions(-DLZO)
endif()

if (NOT MS MATCHES OFF)
  add_subdirectory(compression_libraries/ms_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} ms)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/ms_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/ms_/ms-compress/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/ms_/ms-compress/include/mscomp
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/ms_/src/ms_library.cpp
  )
  add_definitions(-DMS)
endif()

if (NOT SNAPPY MATCHES OFF)
  add_subdirectory(compression_libraries/snappy_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} snappy)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/snappy_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/snappy_/snappy
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/snappy_/src/snappy_library.cpp
  )
  add_definitions(-DSNAPPY)
endif()

if (NOT XPACK MATCHES OFF)
  add_subdirectory(compression_libraries/xpack_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} xpack)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/xpack_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/xpack_/xpack
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/xpack_/src/xpack_library.cpp
  )
  add_definitions(-DXPACK)
endif()

if (NOT ZLIB MATCHES OFF)
  add_subdirectory(compression_libraries/zlib_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} zlibstatic)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/zlib_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/zlib_/zlib
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/zlib_/src/zlib_library.cpp
  )
  add_definitions(-DZLIB)
endif()

if (NOT ZLIB_NG MATCHES OFF)
  add_subdirectory(compression_libraries/zlib-ng_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} ng_zlib)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/zlib-ng_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/zlib-ng_/zlib-ng
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/zlib-ng_/src/zlib-ng_library.cpp
  )
  add_definitions(-DZLIB_NG)
endif()

if (NOT ZSTD MATCHES OFF)
  add_subdirectory(compression_libraries/zstd_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} libzstd_static)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/zstd_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/zstd_/zstd/lib
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/zstd_/src/zstd_library.cpp
  )
  add_definitions(-DZSTD)
endif()

if (NOT LZFX MATCHES OFF)
  add_subdirectory(compression_libraries/lzfx_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lzfx)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzfx_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzfx_/lzfx
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzfx_/src/lzfx_library.cpp
  )
  add_definitions(-DLZFX)
endif()

if (NOT FLZ MATCHES OFF)
  add_subdirectory(compression_libraries/flz_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} flz)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/flz_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/flz_/fastlz
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/flz_/src/flz_library.cpp
  )
  add_definitions(-DFLZ)
endif()

if (NOT GIPFELI MATCHES OFF)
  add_subdirectory(compression_libraries/gipfeli_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} gipfeli)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/gipfeli_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/gipfeli_/gipfeli
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/gipfeli_/src/gipfeli_library.cpp
  )
  add_definitions(-DGIPFELI)
endif()

if (NOT LZF MATCHES OFF)
  add_subdirectory(compression_libraries/lzf_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lzf)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzf_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzf_/liblzf
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzf_/src/lzf_library.cpp
  )
  add_definitions(-DLZF)
endif()

if (NOT LZJB MATCHES OFF)
  add_subdirectory(compression_libraries/lzjb_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lzjb)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzjb_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzjb_/lzjb
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzjb_/src/lzjb_library.cpp
  )
  add_definitions(-DLZJB)
endif()

if (NOT QUICKLZ MATCHES OFF)
  add_subdirectory(compression_libraries/quicklz_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} quicklz)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/quicklz_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/quicklz_/quicklz
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/quicklz_/src/quicklz_library.cpp
  )
  add_definitions(-DQUICKLZ)
endif()

if (NOT WFLZ MATCHES OFF)
  add_subdirectory(compression_libraries/wflz_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} wflz)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/wflz_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/wflz_/wflz
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/wflz_/src/wflz_library.cpp
  )
  add_definitions(-DWFLZ)
endif()

if (NOT YALZ77 MATCHES OFF)
  add_subdirectory(compression_libraries/yalz77_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} yalz77)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/yalz77_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/yalz77_/
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/yalz77_/src/yalz77_library.cpp
  )
  add_definitions(-DYALZ77)
endif()

if (NOT ZPAQ MATCHES OFF)
  add_subdirectory(compression_libraries/zpaq_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} zpaq)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/zpaq_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/zpaq_/zpaq
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/zpaq_/src/zpaq_library.cpp
  )
  add_definitions(-DZPAQ)
endif()

if (NOT LZHAM MATCHES OFF)
  add_subdirectory(compression_libraries/lzham_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lzhamdll)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzham_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzham_/lzham_codec_devel/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzham_/lzham_codec_devel/lzhamcomp
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzham_/lzham_codec_devel/lzhamdecomp
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzham_/src/lzham_library.cpp
  )
  add_definitions(-DLZHAM)
endif()

if (NOT Z3LIB MATCHES OFF)
  add_subdirectory(compression_libraries/z3lib_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} z3lib)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/z3lib_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/z3lib_/z3lib
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/z3lib_/src/z3lib_library.cpp
  )
  add_definitions(-DZ3LIB)
endif()

if (NOT LIBBSC MATCHES OFF)
  add_subdirectory(compression_libraries/libbsc_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} libbsc)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/libbsc_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/libbsc_/libbsc
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/libbsc_/src/libbsc_library.cpp
  )
  add_definitions(-DLIBBSC)
endif()

if (NOT HEATSHRINK MATCHES OFF)
  add_subdirectory(compression_libraries/heatshrink_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} heatshrink)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/heatshrink_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/heatshrink_/heatshrink
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/heatshrink_/src/heatshrink_library.cpp
  )
  add_definitions(-DHEATSHRINK)
endif()

if (NOT ZLING MATCHES OFF)
  add_subdirectory(compression_libraries/zling_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} zling)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/zling_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/zling_/libzling/src
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/zling_/src/zling_library.cpp
  )
  add_definitions(-DZLING)
endif()

if (NOT CSC MATCHES OFF)
  add_subdirectory(compression_libraries/csc_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} csc)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/csc_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/csc_/CSC/src/libcsc
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/csc_/src/csc_library.cpp
  )
  add_definitions(-DCSC)
endif()

if (NOT MINIZ MATCHES OFF)
  add_subdirectory(compression_libraries/miniz_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} miniz)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/miniz_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/miniz_/miniz
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/miniz_/src/miniz_library.cpp
  )
  add_definitions(-DMINIZ)
endif()

if (NOT LIBLZG MATCHES OFF)
  add_subdirectory(compression_libraries/liblzg_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} liblzg)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/liblzg_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/liblzg_/liblzg/src/include
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/liblzg_/src/liblzg_library.cpp
  )
  add_definitions(-DLIBLZG)
endif()

if (NOT FSE MATCHES OFF)
  add_subdirectory(compression_libraries/fse_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} fse)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/fse_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/fse_/FiniteStateEntropy/lib
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/fse_/src/fse_library.cpp
  )
  add_definitions(-DFSE)
endif()

if (NOT UCL MATCHES OFF)
  add_subdirectory(compression_libraries/ucl_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} ucl)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/ucl_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/ucl_/ucl/include
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/ucl_/src/ucl_library.cpp
  )
  add_definitions(-DUCL)
endif()

if (NOT LODEPNG MATCHES OFF)
  add_subdirectory(compression_libraries/lodepng_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lodepng)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lodepng_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lodepng_/lodepng
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lodepng_/src/lodepng_library.cpp
  )
  add_definitions(-DLODEPNG)
endif()

if (NOT FLZMA2 MATCHES OFF)
  add_subdirectory(compression_libraries/flzma2_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} flzma2)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/flzma2_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/flzma2_/fast-lzma2
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/flzma2_/src/flzma2_library.cpp
  )
  add_definitions(-DFLZMA2)
endif()

if (NOT LIZARD MATCHES OFF)
  add_subdirectory(compression_libraries/lizard_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lizard)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lizard_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lizard_/lizard/lib
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lizard_/src/lizard_library.cpp
  )
  add_definitions(-DLIZARD)
endif()

if (NOT PITHY MATCHES OFF)
  add_subdirectory(compression_libraries/pithy_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} pithy)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/pithy_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/pithy_/pithy
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/pithy_/src/pithy_library.cpp
  )
  add_definitions(-DPITHY)
endif()

if (NOT LZMAT MATCHES OFF)
  add_subdirectory(compression_libraries/lzmat_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lzmat)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzmat_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzmat_/lzmat
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzmat_/src/lzmat_library.cpp
  )
  add_definitions(-DLZMAT)
endif()

if(CMAKE_SYSTEM_PROCESSOR STREQUAL x86_64)
  if (NOT LZSSE MATCHES OFF)
    add_subdirectory(compression_libraries/lzsse_)
    set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lzsse)
    set(SMASH_INCLUDES ${SMASH_INCLUDES}
      ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzsse_/include
      ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzsse_/LZSSE/lzsse2
      ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzsse_/LZSSE/lzsse4
      ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzsse_/LZSSE/lzsse8
    )
    set(SMASH_SOURCES ${SMASH_SOURCES}
      ${CMAKE_CURRENT_SOURCE_DIR}/compression_libraries/lzsse_/src/lzsse_library.cpp
    )
    add_definitions(-DLZSSE)
  endif()
endif()
