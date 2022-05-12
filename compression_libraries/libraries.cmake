if (NOT BRIEFLZ MATCHES OFF)
  add_subdirectory(brieflz_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} brieflz)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
      ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/include
      ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/brieflz/include
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
      ${CMAKE_CURRENT_SOURCE_DIR}/brieflz_/src/brieflz_library.cpp
  )
  add_definitions(-DBRIEFLZ)
endif()

if (NOT BROTLI MATCHES OFF)
  add_subdirectory(brotli_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} brotlidec-static brotlienc-static)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/brotli_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/brotli_/brotli/c/include
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/brotli_/src/brotli_library.cpp
  )
  add_definitions(-DBROTLI)
endif()

if (NOT BZIP2 MATCHES OFF)
  add_subdirectory(bzip2_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} bzip2)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/bzip2_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/bzip2_/bzip2
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/bzip2_/src/bzip2_library.cpp
  )
  add_definitions(-DBZIP2)
endif()

if (NOT LZ4 MATCHES OFF)
  add_subdirectory(lz4_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lz4_static)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lz4_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lz4_
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lz4_/src/lz4_library.cpp
  )
  add_definitions(-DLZ4)
endif()

if (NOT CBLOSC2 MATCHES OFF)
  add_subdirectory(c-blosc2_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} blosc2_static)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/c-blosc2_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/c-blosc2_/c-blosc2/include
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/c-blosc2_/src/c-blosc2_library.cpp
  )
  add_definitions(-DCBLOSC2)
endif()

if (NOT DENSITY MATCHES OFF)
  add_subdirectory(density_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} density)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/density_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/density_/density/src
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/density_/src/density_library.cpp
  )
  add_definitions(-DDENSITY)
endif()

if (NOT LIBDEFLATE MATCHES OFF)
  add_subdirectory(libdeflate_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} libdeflate)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate_/libdeflate
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/libdeflate_/src/libdeflate_library.cpp
  )
  add_definitions(-DLIBDEFLATE)
endif()

if (NOT LZFSE MATCHES OFF)
  add_subdirectory(lzfse_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lzfse)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzfse_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lzfse_/lzfse/src
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzfse_/src/lzfse_library.cpp
  )
  add_definitions(-DLZFSE)
endif()

if (NOT LZMA MATCHES OFF)
  add_subdirectory(lzma_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} liblzma)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzma_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lzma_/xz/src/liblzma/api
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzma_/src/lzma_library.cpp
  )
  add_definitions(-DLZMA)
endif()

if (NOT LZO MATCHES OFF)
  add_subdirectory(lzo_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lzo_static_lib)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzo_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lzo_/lzo/include
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzo_/src/lzo_library.cpp
  )
  add_definitions(-DLZO)
endif()

if (NOT MS MATCHES OFF)
  add_subdirectory(ms_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} ms)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/ms_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ms_/ms-compress/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ms_/ms-compress/include/mscomp
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/ms_/src/ms_library.cpp
  )
  add_definitions(-DMS)
endif()

if (NOT SNAPPY MATCHES OFF)
  add_subdirectory(snappy_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} snappy)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/snappy_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/snappy_/snappy
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/snappy_/src/snappy_library.cpp
  )
  add_definitions(-DSNAPPY)
endif()

if (NOT XPACK MATCHES OFF)
  add_subdirectory(xpack_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} xpack)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/xpack_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/xpack_/xpack
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/xpack_/src/xpack_library.cpp
  )
  add_definitions(-DXPACK)
endif()

if (NOT ZLIB MATCHES OFF)
  add_subdirectory(zlib_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} zlibstatic)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/zlib_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/zlib_/zlib
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/zlib_/src/zlib_library.cpp
  )
  add_definitions(-DZLIB)
endif()

if (NOT ZLIB_NG MATCHES OFF)
  add_subdirectory(zlib-ng_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} ng_zlib)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/zlib-ng_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/zlib-ng_/zlib-ng
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/zlib-ng_/src/zlib-ng_library.cpp
  )
  add_definitions(-DZLIB_NG)
endif()

if (NOT ZSTD MATCHES OFF)
  add_subdirectory(zstd_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} libzstd_static)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/zstd_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/zstd_/zstd/lib
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/zstd_/src/zstd_library.cpp
  )
  add_definitions(-DZSTD)
endif()

if (NOT LZFX MATCHES OFF)
  add_subdirectory(lzfx_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lzfx)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzfx_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lzfx_/lzfx
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzfx_/src/lzfx_library.cpp
  )
  add_definitions(-DLZFX)
endif()

if (NOT FLZ MATCHES OFF)
  add_subdirectory(flz_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} flz)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/flz_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/flz_/fastlz
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/flz_/src/flz_library.cpp
  )
  add_definitions(-DFLZ)
endif()

if (NOT GIPFELI MATCHES OFF)
  add_subdirectory(gipfeli_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} gipfeli)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/gipfeli_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/gipfeli_/gipfeli
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/gipfeli_/src/gipfeli_library.cpp
  )
  add_definitions(-DGIPFELI)
endif()

if (NOT LZF MATCHES OFF)
  add_subdirectory(lzf_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lzf)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzf_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lzf_/liblzf
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzf_/src/lzf_library.cpp
  )
  add_definitions(-DLZF)
endif()

if (NOT LZJB MATCHES OFF)
  add_subdirectory(lzjb_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lzjb)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzjb_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lzjb_/lzjb
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzjb_/src/lzjb_library.cpp
  )
  add_definitions(-DLZJB)
endif()

if (NOT QUICKLZ MATCHES OFF)
  add_subdirectory(quicklz_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} quicklz)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/quicklz_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/quicklz_/quicklz
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/quicklz_/src/quicklz_library.cpp
  )
  add_definitions(-DQUICKLZ)
endif()

if (NOT WFLZ MATCHES OFF)
  add_subdirectory(wflz_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} wflz)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/wflz_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/wflz_/wflz
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/wflz_/src/wflz_library.cpp
  )
  add_definitions(-DWFLZ)
endif()

if (NOT YALZ77 MATCHES OFF)
  add_subdirectory(yalz77_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} yalz77)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/yalz77_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/yalz77_/
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/yalz77_/src/yalz77_library.cpp
  )
  add_definitions(-DYALZ77)
endif()

if (NOT ZPAQ MATCHES OFF)
  add_subdirectory(zpaq_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} zpaq)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/zpaq_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/zpaq_/zpaq
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/zpaq_/src/zpaq_library.cpp
  )
  add_definitions(-DZPAQ)
endif()

if (NOT LZHAM MATCHES OFF)
  add_subdirectory(lzham_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lzhamdll)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzham_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lzham_/lzham_codec_devel/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lzham_/lzham_codec_devel/lzhamcomp
    ${CMAKE_CURRENT_SOURCE_DIR}/lzham_/lzham_codec_devel/lzhamdecomp
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzham_/src/lzham_library.cpp
  )
  add_definitions(-DLZHAM)
endif()

if (NOT Z3LIB MATCHES OFF)
  add_subdirectory(z3lib_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} z3lib)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/z3lib_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/z3lib_/z3lib
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/z3lib_/src/z3lib_library.cpp
  )
  add_definitions(-DZ3LIB)
endif()

if (NOT LIBBSC MATCHES OFF)
  add_subdirectory(libbsc_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} libbsc)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/libbsc_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/libbsc_/libbsc
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/libbsc_/src/libbsc_library.cpp
  )
  add_definitions(-DLIBBSC)
endif()

if (NOT HEATSHRINK MATCHES OFF)
  add_subdirectory(heatshrink_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} heatshrink)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/heatshrink_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/heatshrink_/heatshrink
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/heatshrink_/src/heatshrink_library.cpp
  )
  add_definitions(-DHEATSHRINK)
endif()

if (NOT ZLING MATCHES OFF)
  add_subdirectory(zling_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} zling)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/zling_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/zling_/libzling/src
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/zling_/src/zling_library.cpp
  )
  add_definitions(-DZLING)
endif()

if (NOT CSC MATCHES OFF)
  add_subdirectory(csc_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} csc)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/csc_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/csc_/CSC/src/libcsc
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/csc_/src/csc_library.cpp
  )
  add_definitions(-DCSC)
endif()

if (NOT MINIZ MATCHES OFF)
  add_subdirectory(miniz_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} miniz)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/miniz_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/miniz_/miniz
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/miniz_/src/miniz_library.cpp
  )
  add_definitions(-DMINIZ)
endif()

if (NOT LIBLZG MATCHES OFF)
  add_subdirectory(liblzg_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} liblzg)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/liblzg_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/liblzg_/liblzg/src/include
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/liblzg_/src/liblzg_library.cpp
  )
  add_definitions(-DLIBLZG)
endif()

if (NOT FSE MATCHES OFF)
  add_subdirectory(fse_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} fse)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/fse_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/fse_/FiniteStateEntropy/lib
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/fse_/src/fse_library.cpp
  )
  add_definitions(-DFSE)
endif()

if (NOT UCL MATCHES OFF)
  add_subdirectory(ucl_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} ucl)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/ucl_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ucl_/ucl/include
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/ucl_/src/ucl_library.cpp
  )
  add_definitions(-DUCL)
endif()

if (NOT LODEPNG MATCHES OFF)
  add_subdirectory(lodepng_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lodepng)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lodepng_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lodepng_/lodepng
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lodepng_/src/lodepng_library.cpp
  )
  add_definitions(-DLODEPNG)
endif()

if (NOT FLZMA2 MATCHES OFF)
  add_subdirectory(flzma2_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} flzma2)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/flzma2_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/flzma2_/fast-lzma2
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/flzma2_/src/flzma2_library.cpp
  )
  add_definitions(-DFLZMA2)
endif()

if (NOT LIZARD MATCHES OFF)
  add_subdirectory(lizard_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lizard)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lizard_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lizard_/lizard/lib
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lizard_/src/lizard_library.cpp
  )
  add_definitions(-DLIZARD)
endif()

if (NOT PITHY MATCHES OFF)
  add_subdirectory(pithy_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} pithy)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/pithy_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/pithy_/pithy
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/pithy_/src/pithy_library.cpp
  )
  add_definitions(-DPITHY)
endif()

if (NOT LZMAT MATCHES OFF)
  add_subdirectory(lzmat_)
  set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lzmat)
  set(SMASH_INCLUDES ${SMASH_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzmat_/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lzmat_/lzmat
  )
  set(SMASH_SOURCES ${SMASH_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lzmat_/src/lzmat_library.cpp
  )
  add_definitions(-DLZMAT)
endif()

if(CMAKE_SYSTEM_PROCESSOR STREQUAL x86_64)
  if (NOT LZSSE MATCHES OFF)
    add_subdirectory(lzsse_)
    set(SMASH_LIBRARIES ${SMASH_LIBRARIES} lzsse)
    set(SMASH_INCLUDES ${SMASH_INCLUDES}
      ${CMAKE_CURRENT_SOURCE_DIR}/lzsse_/include
      ${CMAKE_CURRENT_SOURCE_DIR}/lzsse_/LZSSE/lzsse2
      ${CMAKE_CURRENT_SOURCE_DIR}/lzsse_/LZSSE/lzsse4
      ${CMAKE_CURRENT_SOURCE_DIR}/lzsse_/LZSSE/lzsse8
    )
    set(SMASH_SOURCES ${SMASH_SOURCES}
      ${CMAKE_CURRENT_SOURCE_DIR}/lzsse_/src/lzsse_library.cpp
    )
    add_definitions(-DLZSSE)
  endif()
endif()
