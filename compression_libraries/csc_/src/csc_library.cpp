/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <Types.h>
#include <csc_dec.h>
#include <csc_enc.h>
#include <string.h>

// SMASH LIBRARIES
#include <csc_library.hpp>
#include <options.hpp>

SRes CscReader::RealRead(void *istream, void *buf, size_t *size) {
  CscReader *reader = reinterpret_cast<CscReader *>(istream);
  *size = reader->GetData(buf, *size);
  return 0;
}

size_t CscReader::GetData(void *buf, size_t len) {
  uint64_t real_size{0};
  if (buf && len && buffer_ && buffer_size_) {
    real_size = (len > buffer_size_) ? buffer_size_ : len;
    memcpy(buf, buffer_, real_size);
    buffer_ += real_size;
    buffer_size_ -= real_size;
    total_read_ += real_size;
  }
  return real_size;
}

size_t CscReader::GetInputSize() { return total_read_; }

CscReader::CscReader(char *buffer, const uint64_t &buffer_size)
    : buffer_(buffer), buffer_size_(buffer_size), total_read_(0) {
  Read = CscReader::RealRead;
}

size_t CscWriter::RealWrite(void *ostream, const void *buf, size_t size) {
  CscWriter *writer = reinterpret_cast<CscWriter *>(ostream);
  return writer->PutData(buf, size);
}

size_t CscWriter::PutData(const void *buf, size_t len) {
  uint64_t real_size{0};
  if (buf && len && buffer_ && buffer_size_) {
    real_size = (len > buffer_size_) ? buffer_size_ : len;
    memcpy(buffer_, buf, real_size);
    buffer_ += real_size;
    buffer_size_ -= real_size;
    total_write_ += real_size;
  }
  return real_size;
}

size_t CscWriter::GetOutputSize() { return total_write_; }

CscWriter::CscWriter(char *buffer, const uint64_t &buffer_size)
    : buffer_(buffer), buffer_size_(buffer_size), total_write_(0) {
  Write = CscWriter::RealWrite;
}

bool CscLibrary::CheckOptions(Options *options, const bool &compressor) {
  bool result{true};
  if (compressor) {
    result = CompressionLibrary::CheckCompressionLevel("csc", options, 1, 5);
    if (result) {
      result = CompressionLibrary::CheckWindowSize("csc", options, 15, 29);
      if (result) {
        result = CompressionLibrary::CheckFlags("csc", options, 0, 7);
      }
    }
  }
  return result;
}

bool CscLibrary::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                          char *compressed_data, uint64_t *compressed_size) {
  bool result{initialized_compressor_};
  if (result) {
    CSCProps props;

    CSCEncProps_Init(&props, 1 << options_.GetWindowSize(),
                     options_.GetCompressionLevel());

    props.DLTFilter = options_.GetFlags() & 1;
    props.EXEFilter = options_.GetFlags() & 2;
    props.TXTFilter = options_.GetFlags() & 4;

    CSCEnc_WriteProperties(&props, reinterpret_cast<uint8_t *>(compressed_data),
                           0);
    CscReader reader(uncompressed_data, uncompressed_size);
    CscWriter writer(compressed_data + CSC_PROP_SIZE, *compressed_size);
    CSCEncHandle handle = CSCEnc_Create(
        &props, reinterpret_cast<ISeqOutStream *>(&writer), nullptr);
    if (result = handle) {
      int csc_result = CSCEnc_Encode(
          handle, reinterpret_cast<ISeqInStream *>(&reader), nullptr);
      if (result = (csc_result == 0)) {
        csc_result = CSCEnc_Encode_Flush(handle);
        result = (csc_result == 0);
      }
      CSCEnc_Destroy(handle);
    }
    if (!result) {
      std::cout << "ERROR: csc error when compress data" << std::endl;
    }
    *compressed_size = writer.GetOutputSize() + CSC_PROP_SIZE;
  }
  return result;
}

bool CscLibrary::Decompress(char *compressed_data, uint64_t compressed_size,
                            char *decompressed_data,
                            uint64_t *decompressed_size) {
  bool result{initialized_decompressor_};
  if (result) {
    CSCProps props;
    CscReader reader(compressed_data, compressed_size);
    CscWriter writer(decompressed_data, *decompressed_size);

    unsigned char buf[CSC_PROP_SIZE];
    reader.GetData(buf, CSC_PROP_SIZE);
    CSCDec_ReadProperties(&props, buf);
    CSCDecHandle handle = CSCDec_Create(
        &props, reinterpret_cast<ISeqInStream *>(&reader), nullptr);
    if (result = handle) {
      int csc_result = CSCDec_Decode(
          handle, reinterpret_cast<ISeqOutStream *>(&writer), nullptr);
      result = (csc_result == 0);
      CSCDec_Destroy(handle);
    }
    if (!result) {
      std::cout << "ERROR: csc error when decompress data" << std::endl;
    }
    *decompressed_size = writer.GetOutputSize();
  }
  return result;
}

void CscLibrary::GetTitle() {
  CompressionLibrary::GetTitle(
      "csc", "A Loss-less data compression algorithm inspired by LZMA");
}

bool CscLibrary::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  if (minimum_level) *minimum_level = 1;
  if (maximum_level) *maximum_level = 5;
  if (compression_level_information) {
    compression_level_information->clear();
    compression_level_information->push_back("Available values [1-5]");
    compression_level_information->push_back("[compression]");
  }
  return true;
}

bool CscLibrary::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  if (minimum_size) *minimum_size = 15;
  if (maximum_size) *maximum_size = 29;
  if (window_size_information) {
    window_size_information->clear();
    window_size_information->push_back("Available values [15-29]");
    window_size_information->push_back("Window size = (2^value)");
    window_size_information->push_back("[compression]");
  }
  return true;
}

bool CscLibrary::GetFlagsInformation(
    std::vector<std::string> *flags_information, uint8_t *minimum_flags,
    uint8_t *maximum_flags) {
  if (minimum_flags) *minimum_flags = 0;
  if (maximum_flags) *maximum_flags = 7;
  if (flags_information) {
    flags_information->clear();
    flags_information->push_back("Available values [0-7]");
    flags_information->push_back("0: " + flags_[0]);
    flags_information->push_back("1: " + flags_[1]);
    flags_information->push_back("2: " + flags_[2]);
    flags_information->push_back("3: " + flags_[3]);
    flags_information->push_back("4: " + flags_[4]);
    flags_information->push_back("5: " + flags_[5]);
    flags_information->push_back("6: " + flags_[6]);
    flags_information->push_back("7: " + flags_[7]);
    flags_information->push_back("[compression]");
  }
  return true;
}

std::string CscLibrary::GetFlagsName(const uint8_t &flags) {
  std::string result = "ERROR";
  if (flags < number_of_flags_) {
    result = flags_[flags];
  }
  return result;
}

CscLibrary::CscLibrary() {
  number_of_flags_ = 8;
  flags_ = new std::string[number_of_flags_];
  flags_[0] = "None";
  flags_[1] = "Delta";
  flags_[2] = "Exe";
  flags_[3] = "1 & 2";
  flags_[4] = "Text";
  flags_[5] = "1 & 4";
  flags_[6] = "2 & 4";
  flags_[7] = "1 & 2 & 4";
}

CscLibrary::~CscLibrary() { delete[] flags_; }
