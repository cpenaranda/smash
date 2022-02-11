/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <brotli/decode.h>
#include <brotli/encode.h>
#include <math.h>

// SMASH LIBRARIES
#include <brotli_library.hpp>
#include <options.hpp>

bool BrotliLibrary::checkOptions(Options opt) {
  bool result{true};
  if (opt.getCompressionLevel() > 11) {
    std::cout
        << "ERROR: Compression level can not be higher than 11 using brotli"
        << std::endl;
    result = false;
  } else if (opt.getMode() > 2) {
    std::cout << "ERROR: Mode can not be higher than 2 using brotli"
              << std::endl;
    result = false;
  } else if (opt.getWindowSize() > 24) {
    std::cout << "ERROR: Window size can not be higher than 24 using brotli"
              << std::endl;
    result = false;
  } else if (opt.getWindowSize() < 10 && opt.getWindowSize() > 0) {
    std::cout << "ERROR: Window size can not be higher than 0 and lower than "
                 "10 using brotli"
              << std::endl;
    result = false;
  }
  return result;
}

void BrotliLibrary::getCompressDataSize(uint64_t uncompress_size,
                                        uint64_t *compress_size) {
  *compress_size = BrotliEncoderMaxCompressedSize(uncompress_size);
}

bool BrotliLibrary::compress(Options opt, char *uncompress_data,
                             uint64_t uncompress_size, char *compress_data,
                             uint64_t *compress_size) {
  bool result = checkOptions(opt);
  if (result) {
    BrotliEncoderMode mode;

    switch (opt.getMode()) {
      case 0:
        mode = BrotliEncoderMode::BROTLI_MODE_GENERIC;
        break;
      case 1:
        mode = BrotliEncoderMode::BROTLI_MODE_TEXT;
        break;
      case 2:
        mode = BrotliEncoderMode::BROTLI_MODE_FONT;
        break;
      default:
        break;
    }

    if (result &&
        !BrotliEncoderCompress(
            opt.getCompressionLevel(), opt.getWindowSize(), mode,
            uncompress_size, reinterpret_cast<uint8_t *>(uncompress_data),
            compress_size, reinterpret_cast<uint8_t *>(compress_data))) {
      std::cout << "ERROR: brotli error when compress data" << std::endl;
      result = false;
    }
  }
  return result;
}

bool BrotliLibrary::decompress(char *compress_data, uint64_t compress_size,
                               char *decompress_data,
                               uint64_t *decompress_size) {
  bool result{true};
  if (BROTLI_DECODER_RESULT_SUCCESS !=
      BrotliDecoderDecompress(
          compress_size, reinterpret_cast<uint8_t *>(compress_data),
          decompress_size, reinterpret_cast<uint8_t *>(decompress_data))) {
    std::cout << "ERROR: brotli error when decompress data" << std::endl;
    result = false;
  }
  return result;
}

void BrotliLibrary::getTitle() {
  CompressionLibrary::getTitle("brotli",
                               "General-puprose compression algorithm");
}

BrotliLibrary::BrotliLibrary() {}

BrotliLibrary::~BrotliLibrary() {}
