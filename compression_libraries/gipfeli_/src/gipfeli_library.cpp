/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <gipfeli-internal.h>

// CPU-SMASH LIBRARIES
#include <cpu_options.hpp>
#include <gipfeli_library.hpp>

bool GipfeliLibrary::SetOptionsCompressor(CpuOptions *options) {
  if (initialized_decompressor_) initialized_decompressor_ = false;
  initialized_compressor_ = CheckOptions(options, true);
  if (initialized_compressor_) {
    options_ = *options;
    if (compressor_) {
      delete compressor_;
    }
    compressor_ = new util::compression::gipfeli::Gipfeli();
  }
  return initialized_compressor_;
}

bool GipfeliLibrary::SetOptionsDecompressor(CpuOptions *options) {
  if (initialized_compressor_) initialized_compressor_ = false;
  initialized_decompressor_ = CheckOptions(options, false);
  if (initialized_decompressor_) {
    options_ = *options;
    if (compressor_) {
      delete compressor_;
    }
    compressor_ = new util::compression::gipfeli::Gipfeli();
  }
  return initialized_decompressor_;
}

void GipfeliLibrary::GetCompressedDataSize(
    const char *const uncompressed_data, const uint64_t &uncompressed_data_size,
    uint64_t *compressed_data_size) {
  util::compression::Compressor *compressor =
      util::compression::NewGipfeliCompressor();

  *compressed_data_size =
      compressor->MaxCompressedLength(uncompressed_data_size);

  delete compressor;
}

bool GipfeliLibrary::Compress(const char *const uncompressed_data,
                              const uint64_t &uncompressed_data_size,
                              char *compressed_data,
                              uint64_t *compressed_data_size) {
  bool result{initialized_compressor_};
  if (result) {
    uint64_t real_compressed_size = compressor_->RawCompress(
        std::string(uncompressed_data, uncompressed_data_size),
        compressed_data);
    if (real_compressed_size > *compressed_data_size) {
      std::cout << "ERROR: gipfeli error when compress data" << std::endl;
      result = false;
    }
    *compressed_data_size = real_compressed_size;
  }
  return result;
}

bool GipfeliLibrary::Decompress(const char *const compressed_data,
                                const uint64_t &compressed_data_size,
                                char *decompressed_data,
                                uint64_t *decompressed_data_size) {
  bool result{initialized_decompressor_};
  if (result) {
    bool gipfeli_result =
        compressor_->RawUncompress(compressed_data, compressed_data_size,
                                   decompressed_data, *decompressed_data_size);
    if (!gipfeli_result) {
      std::cout << "ERROR: gipfeli error when decompress data" << std::endl;
      result = false;
    }
  }
  return result;
}

void GipfeliLibrary::GetDecompressedDataSize(
    const char *const compressed_data, const uint64_t &compressed_data_size,
    uint64_t *decompressed_data_size) {
  util::compression::Compressor *compressor =
      util::compression::NewGipfeliCompressor();

  compressor->GetUncompressedLength(compressed_data, decompressed_data_size);

  delete compressor;
}

void GipfeliLibrary::GetTitle() {
  CpuCompressionLibrary::GetTitle(
      "gipfeli",
      "High-speed compression/decompression library aiming at slightly higher "
      "compression ratios than other high-speed compression libraries");
}

GipfeliLibrary::GipfeliLibrary() { compressor_ = nullptr; }

GipfeliLibrary::~GipfeliLibrary() {
  if (compressor_) delete compressor_;
}
