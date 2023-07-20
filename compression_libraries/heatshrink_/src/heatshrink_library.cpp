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

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <heatshrink_library.hpp>

bool HeatshrinkLibrary::CheckOptions(CpuOptions *options,
                                     const bool &compressor) {
  bool result{true};

  result = CpuCompressionLibrary::CheckWindowSize("heatshrink", options, 4, 14);
  if (result) {
    result = CpuCompressionLibrary::CheckBackReference(
        "heatshrink", options, 3, options->GetWindowSize() - 1);
  }
  return result;
}

bool HeatshrinkLibrary::Compress(const char *const uncompressed_data,
                                 const uint64_t &uncompressed_data_size,
                                 char *compressed_data,
                                 uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    heatshrink_encoder *compression = heatshrink_encoder_alloc(
        options_.GetWindowSize(), options_.GetBackReference());
    if (result = compression) {
      uint64_t size{0};
      uint64_t bytes{0};
      HSE_sink_res sres;
      HSE_poll_res pres;
      HSE_finish_res fres;
      uint64_t current_uncompressed_data_size{uncompressed_data_size};
      uint8_t *current_uncompressed_data = const_cast<uint8_t *>(
          reinterpret_cast<const uint8_t *const>(uncompressed_data));
      while (current_uncompressed_data_size && result) {
        sres = heatshrink_encoder_sink(
            compression, reinterpret_cast<uint8_t *>(current_uncompressed_data),
            current_uncompressed_data_size, &size);
        result = (sres >= 0) && (size <= current_uncompressed_data_size);
        if (result && size) {
          current_uncompressed_data += size;
          current_uncompressed_data_size -= size;
        }
        if (!current_uncompressed_data_size && result) {
          fres = heatshrink_encoder_finish(compression);
          result = (fres == HSER_FINISH_MORE);
        }
        for (pres = HSER_POLL_MORE; pres == HSER_POLL_MORE && result;) {
          pres = heatshrink_encoder_poll(
              compression, reinterpret_cast<uint8_t *>(compressed_data),
              *compressed_data_size, &size);
          result = (pres >= 0) && (bytes + size <= *compressed_data_size);
          if (result && size) {
            bytes += size;
            compressed_data += size;
          }
        }
      }
      if (result) {
        fres = heatshrink_encoder_finish(compression);
        if (fres < 0 || fres != HSER_FINISH_DONE ||
            bytes > *compressed_data_size) {
          result = false;
        }
      }
      *compressed_data_size = bytes;
      heatshrink_encoder_free(compression);
    }
    if (!result) {
      std::cout << "ERROR: heatshrink error when compress data" << std::endl;
    }
  }
  return result;
}

bool HeatshrinkLibrary::Decompress(const char *const compressed_data,
                                   const uint64_t &compressed_data_size,
                                   char *decompressed_data,
                                   uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    heatshrink_decoder *decompression = heatshrink_decoder_alloc(
        256, options_.GetWindowSize(), options_.GetBackReference());
    if (result = decompression) {
      uint64_t size{0};
      uint64_t bytes = 0;
      HSD_sink_res sres;
      HSD_poll_res pres;
      HSD_finish_res fres;
      uint64_t current_compressed_data_size{compressed_data_size};
      uint8_t *current_compressed_data = const_cast<uint8_t *>(
          reinterpret_cast<const uint8_t *const>(compressed_data));
      while (current_compressed_data_size && result) {
        sres = heatshrink_decoder_sink(
            decompression, reinterpret_cast<uint8_t *>(current_compressed_data),
            current_compressed_data_size, &size);
        result = (sres >= 0) && (size <= current_compressed_data_size);
        if (result && size) {
          current_compressed_data += size;
          current_compressed_data_size -= size;
        }
        if (!current_compressed_data_size && result) {
          fres = heatshrink_decoder_finish(decompression);
          result = (fres == HSDR_FINISH_MORE);
        }
        for (pres = HSDR_POLL_MORE; pres == HSDR_POLL_MORE && result;) {
          pres = heatshrink_decoder_poll(
              decompression, reinterpret_cast<uint8_t *>(decompressed_data),
              *decompressed_data_size, &size);
          result = (pres >= 0) && (bytes + size <= *decompressed_data_size);
          if (result && size) {
            bytes += size;
            decompressed_data += size;
          }
        }
      }
      if (result) {
        fres = heatshrink_decoder_finish(decompression);
        if (fres < 0 || fres != HSDR_FINISH_DONE ||
            bytes > *decompressed_data_size) {
          result = false;
        }
      }
      *decompressed_data_size = bytes;
      heatshrink_decoder_free(decompression);
    }
    if (!result) {
      std::cout << "ERROR: heatshrink error when decompress data" << std::endl;
    }
  }
  return result;
}

void HeatshrinkLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle("heatshrink",
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

bool HeatshrinkLibrary::GetBackReferenceInformation(
    std::vector<std::string> *back_reference_information,
    uint8_t *minimum_back_reference, uint8_t *maximum_back_reference) {
  if (minimum_back_reference) *minimum_back_reference = 3;
  if (maximum_back_reference) *maximum_back_reference = 0;
  if (back_reference_information) {
    back_reference_information->clear();
    back_reference_information->push_back(
        "Available values [3 - <window_size>[");
    back_reference_information->push_back("[compression/decompression]");
  }
  return true;
}

HeatshrinkLibrary::HeatshrinkLibrary() {}

HeatshrinkLibrary::~HeatshrinkLibrary() {}
