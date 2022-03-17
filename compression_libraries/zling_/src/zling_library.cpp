/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <libzling.h>

// SMASH LIBRARIES
#include <options.hpp>
#include <zling_library.hpp>

size_t ZlingReader::GetData(unsigned char *buf, size_t len) {
  uint64_t real_size{0};
  if (buf && len && buffer_ && buffer_size_) {
    real_size = (len > buffer_size_) ? buffer_size_ : len;
    memcpy(buf, buffer_, real_size);
    buffer_ += real_size;
    buffer_size_ -= real_size;
    total_read_ += real_size;
  } else {
    error_ = true;
  }
  return real_size;
}

bool ZlingReader::IsEnd() { return !buffer_size_; }

bool ZlingReader::IsErr() { return error_; }

size_t ZlingReader::GetInputSize() { return total_read_; }

ZlingReader::ZlingReader(char *buffer, const uint64_t &buffer_size)
    : buffer_(buffer),
      buffer_size_(buffer_size),
      total_read_(0),
      error_(false) {}

size_t ZlingWriter::PutData(unsigned char *buf, size_t len) {
  uint64_t real_size{0};
  if (buf && len && buffer_ && buffer_size_) {
    real_size = (len > buffer_size_) ? buffer_size_ : len;
    memcpy(buffer_, buf, real_size);
    buffer_ += real_size;
    buffer_size_ -= real_size;
    total_write_ += real_size;
  } else {
    error_ = true;
  }
  return real_size;
}

bool ZlingWriter::IsErr() { return error_; }

size_t ZlingWriter::GetOutputSize() { return total_write_; }

ZlingWriter::ZlingWriter(char *buffer, const uint64_t &buffer_size)
    : buffer_(buffer),
      buffer_size_(buffer_size),
      total_write_(0),
      error_(false) {}

bool ZlingLibrary::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel("zling", options, 0, 4);
  }
  return result;
}

bool ZlingLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                            char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    ZlingReader reader(uncompressed_data, uncompressed_size);
    ZlingWriter writer(compressed_data, *compressed_size);
    int zling_result = baidu::zling::Encode(&reader, &writer, NULL,
                                            options_.GetCompressionLevel());
    if (zling_result != 0) {
      std::cout << "ERROR: zling error when compress data" << std::endl;
      result = false;
    }
    *compressed_size = writer.GetOutputSize();
  }
  return result;
}

bool ZlingLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                              char *decompressed_data,
                              uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    ZlingReader reader(compressed_data, compressed_size);
    ZlingWriter writer(decompressed_data, *decompressed_size);
    int zling_result = baidu::zling::Decode(&reader, &writer, NULL);
    if (zling_result != 0) {
      std::cout << "ERROR: zling error when decompress data" << std::endl;
      result = false;
    }
    *decompressed_size = writer.GetOutputSize();
  }
  return result;
}

void ZlingLibrary::GetTitle() {
  CompressionLibrary::GetTitle("zling",
                               "Lightweight compression library using fast "
                               "order-1 ROLZ followed with Huffman encoding");
}

bool ZlingLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 0;
  if (maximum_level) *maximum_level = 4;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [0-4]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

ZlingLibrary::ZlingLibrary() {}

ZlingLibrary::~ZlingLibrary() {}
