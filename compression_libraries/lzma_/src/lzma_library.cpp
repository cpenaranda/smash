/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <lzma.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <lzma_library.hpp>

bool LzmaLibrary::checkOptions(Options opt) {
  bool result{true};
  if (opt.getMode() > 2) {
    std::cout << "ERROR: Mode can not be higher than 2 using lzma" << std::endl;
    result = false;
  } else if (opt.getNumberThreads() < 1) {
    std::cout << "ERROR: Number of threads can not be lower than 1 using lzma"
              << std::endl;
    result = false;
  }
  return result;
}

void LzmaLibrary::getCompressDataSize(uint64_t uncompress_size,
                                    uint64_t *compress_size) {
  *compress_size = lzma_stream_buffer_bound(uncompress_size);
}

bool LzmaLibrary::compress(Options opt, char *uncompress_data,
                         uint64_t uncompress_size, char *compress_data,
                         uint64_t *compress_size) {
  bool result = checkOptions(opt);
  if (result) {
    lzma_stream strm = LZMA_STREAM_INIT;
    lzma_filter filters[2];
    lzma_options_lzma lzma_options;
    lzma_mt config;
    config.flags = 0;
    config.block_size = 0;
    config.timeout = 0;
    config.check = LZMA_CHECK_CRC64;
    switch (opt.getMode()) {
      case 0:
        config.preset = LZMA_PRESET_DEFAULT;
        config.filters = nullptr;
        break;
      case 1:
        config.preset = LZMA_PRESET_EXTREME;
        config.filters = nullptr;
        break;
      case 2:
        config.preset = LZMA_PRESET_DEFAULT;
        lzma_lzma_preset(&lzma_options, LZMA_PRESET_DEFAULT);
        filters[1].id = LZMA_VLI_UNKNOWN;
        filters[1].options = nullptr;
        filters[0].id = LZMA_FILTER_LZMA2;
        filters[0].options = &lzma_options;
        config.filters = filters;
        break;
      default:
        break;
    }
    config.threads = opt.getNumberThreads();

    lzma_ret ret_lzma = lzma_stream_encoder_mt(&strm, &config);

    if (ret_lzma != LZMA_OK) {
      result = false;
    } else {
      uint64_t size_aux{0};
      strm.next_in = reinterpret_cast<uint8_t *>(uncompress_data);
      strm.avail_in = uncompress_size;
      strm.next_out = reinterpret_cast<uint8_t *>(compress_data);
      strm.avail_out = *compress_size;
      ret_lzma = lzma_code(&strm, LZMA_RUN);
      if (ret_lzma != LZMA_OK) {
        result = false;

      } else {
        size_aux = strm.avail_out;
        ret_lzma = lzma_code(&strm, LZMA_FINISH);
        if (ret_lzma != LZMA_STREAM_END) {
          result = false;

        } else {
          *compress_size =
              (*compress_size - size_aux) + (size_aux - strm.avail_out);
        }
      }
    }
    lzma_end(&strm);
    if (!result) {
      std::cout << "ERROR: lzma error when compress data" << std::endl;
    }
  }
  return result;
}

bool LzmaLibrary::decompress(char *compress_data, uint64_t compress_size,
                           char *decompress_data, uint64_t *decompress_size) {
  bool result{true};
  lzma_stream strm = LZMA_STREAM_INIT;
  lzma_ret ret_lzma = lzma_stream_decoder(
      &strm, UINT64_MAX, LZMA_TELL_UNSUPPORTED_CHECK | LZMA_CONCATENATED);
  if (ret_lzma != LZMA_OK) {
    result = false;
  } else {
    uint64_t size_aux{0};
    strm.next_in = reinterpret_cast<uint8_t *>(compress_data);
    strm.avail_in = compress_size;
    strm.next_out = reinterpret_cast<uint8_t *>(decompress_data);
    strm.avail_out = *decompress_size;

    ret_lzma = lzma_code(&strm, LZMA_RUN);

    if (ret_lzma != LZMA_OK) {
      result = false;
    } else {
      size_aux = strm.avail_out;
      ret_lzma = lzma_code(&strm, LZMA_FINISH);
      if (ret_lzma != LZMA_STREAM_END) {
        result = false;
      } else {
        *decompress_size =
            (*decompress_size - size_aux) + (size_aux - strm.avail_out);
      }
    }
    lzma_end(&strm);
  }
  if (!result) {
    std::cout << "ERROR: lzma error when decompress data" << std::endl;
  }
  return result;
}

void LzmaLibrary::getTitle() {
  CompressionLibrary::getTitle("lzma",
                               "A general-purpose data-compression library");
}

LzmaLibrary::LzmaLibrary() {}

LzmaLibrary::~LzmaLibrary() {}
