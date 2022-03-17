/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */
extern "C" {
#include <heatshrink_decoder.h>
#include <heatshrink_encoder.h>
}

// SMASH LIBRARIES
#include <heatshrink_library.hpp>
#include <options.hpp>

bool HeatshrinkLibrary::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};

  result = CompressionLibrary::CheckWindowSize("heatshrink", options, 4, 14);
  if (result) {
    result = CompressionLibrary::CheckBackReferenceBits(
        "heatshrink", options, 3, options->GetWindowSize() - 1);
  }
  return result;
}

bool HeatshrinkLibrary::Compress(char *uncompressed_data,
                                 uint64_t uncompressed_size,
                                 char *compressed_data,
                                 uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    heatshrink_encoder *compression = heatshrink_encoder_alloc(
        options_.GetWindowSize(), options_.GetBackReferenceBits());
    if (result = compression) {
      uint64_t size{0};
      uint64_t bytes{0};
      HSE_sink_res sres;
      HSE_poll_res pres;
      HSE_finish_res fres;

      while (uncompressed_size && result) {
        sres = heatshrink_encoder_sink(
            compression, reinterpret_cast<uint8_t *>(uncompressed_data),
            uncompressed_size, &size);
        result = (sres >= 0) && (size <= uncompressed_size);
        if (result && size) {
          uncompressed_data += size;
          uncompressed_size -= size;
        }
        if (!uncompressed_size && result) {
          fres = heatshrink_encoder_finish(compression);
          result = (fres == HSER_FINISH_MORE);
        }
        for (pres = HSER_POLL_MORE; pres == HSER_POLL_MORE && result;) {
          pres = heatshrink_encoder_poll(
              compression, reinterpret_cast<uint8_t *>(compressed_data),
              *compressed_size, &size);
          result = (pres >= 0) && (bytes + size <= *compressed_size);
          if (result && size) {
            bytes += size;
            compressed_data += size;
          }
        }
      }
      if (result) {
        fres = heatshrink_encoder_finish(compression);
        if (fres < 0 || fres != HSER_FINISH_DONE || bytes > *compressed_size) {
          result = false;
        }
      }
      *compressed_size = bytes;
      heatshrink_encoder_free(compression);
    }
    if (!result) {
      std::cout << "ERROR: heatshrink error when compress data" << std::endl;
    }
  }
  return result;
}

bool HeatshrinkLibrary::Decompress(char *compressed_data,
                                   uint64_t compressed_size,
                                   char *decompressed_data,
                                   uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    heatshrink_decoder *decompression = heatshrink_decoder_alloc(
        256, options_.GetWindowSize(), options_.GetBackReferenceBits());
    if (result = decompression) {
      uint64_t size{0};
      uint64_t bytes = 0;
      HSD_sink_res sres;
      HSD_poll_res pres;
      HSD_finish_res fres;

      while (compressed_size && result) {
        sres = heatshrink_decoder_sink(
            decompression, reinterpret_cast<uint8_t *>(compressed_data),
            compressed_size, &size);
        result = (sres >= 0) && (size <= compressed_size);
        if (result && size) {
          compressed_data += size;
          compressed_size -= size;
        }
        if (!compressed_size && result) {
          fres = heatshrink_decoder_finish(decompression);
          result = (fres == HSDR_FINISH_MORE);
        }
        for (pres = HSDR_POLL_MORE; pres == HSDR_POLL_MORE && result;) {
          pres = heatshrink_decoder_poll(
              decompression, reinterpret_cast<uint8_t *>(decompressed_data),
              *decompressed_size, &size);
          result = (pres >= 0) && (bytes + size <= *decompressed_size);
          if (result && size) {
            bytes += size;
            decompressed_data += size;
          }
        }
      }
      if (result) {
        fres = heatshrink_decoder_finish(decompression);
        if (fres < 0 || fres != HSDR_FINISH_DONE ||
            bytes > *decompressed_size) {
          result = false;
        }
      }
      *decompressed_size = bytes;
      heatshrink_decoder_free(decompression);
    }
    if (!result) {
      std::cout << "ERROR: heatshrink error when decompress data" << std::endl;
    }
  }
  return result;
}

void HeatshrinkLibrary::GetTitle() {
  CompressionLibrary::GetTitle("heatshrink",
                               "LZ77-based compression library targeted at "
                               "embedded and real-time systems");
}

bool HeatshrinkLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 4;
  if (maximum_size) *maximum_size = 14;
  if (window_size_information) {
    window_size_information->clear();
    window_size_information->push_back("Available values [4 - 14]");
    window_size_information->push_back("[compression/decompression]");
  }
  return true;
}

bool HeatshrinkLibrary::GetBackReferenceBitsInformation(
    std::vector<std::string> *back_reference_bits_information,
    uint8_t *minimum_bits, uint8_t *maximum_bits) {
  if (minimum_bits) *minimum_bits = 3;
  if (maximum_bits) *maximum_bits = 0;
  if (back_reference_bits_information) {
    back_reference_bits_information->clear();
    back_reference_bits_information->push_back(
        "Available values [3 - <window_size>[");
    back_reference_bits_information->push_back("[compression/decompression]");
  }
  return true;
}

HeatshrinkLibrary::HeatshrinkLibrary() {}

HeatshrinkLibrary::~HeatshrinkLibrary() {}
