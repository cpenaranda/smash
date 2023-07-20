/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

// CPU-SMASH LIBRARIES
#include <cpu_compression_libraries.hpp>
#include <cpu_smash.hpp>

bool CpuSmash::SetOptionsCompressor(CpuOptions *options) {
  return lib->SetOptionsCompressor(options);
}

bool CpuSmash::SetOptionsDecompressor(CpuOptions *options) {
  return lib->SetOptionsDecompressor(options);
}

void CpuSmash::GetCompressedDataSize(const char *const uncompressed_data,
                                     const uint64_t &uncompressed_data_size,
                                     uint64_t *compressed_data_size) {
  lib->GetCompressedDataSize(uncompressed_data, uncompressed_data_size,
                             compressed_data_size);
}

bool CpuSmash::Compress(const char *const uncompressed_data,
                        const uint64_t &uncompressed_data_size,
                        char *compressed_data, uint64_t *compressed_data_size) {
  return lib->Compress(uncompressed_data, uncompressed_data_size,
                       compressed_data, compressed_data_size);
}

void CpuSmash::GetDecompressedDataSize(const char *const compressed_data,
                                       const uint64_t &compressed_data_size,
                                       uint64_t *decompressed_data_size) {
  lib->GetDecompressedDataSize(compressed_data, compressed_data_size,
                               decompressed_data_size);
}

bool CpuSmash::Decompress(const char *const compressed_data,
                          const uint64_t &compressed_data_size,
                          char *decompressed_data,
                          uint64_t *decompressed_data_size) {
  return lib->Decompress(compressed_data, compressed_data_size,
                         decompressed_data, decompressed_data_size);
}

void CpuSmash::GetTitle() { lib->GetTitle(); }

bool CpuSmash::CompareData(const char *const uncompressed_data,
                           const uint64_t &uncompressed_data_size,
                           const char *const decompressed_data,
                           const uint64_t &decompressed_data_size) {
  return lib->CompareData(uncompressed_data, uncompressed_data_size,
                          decompressed_data, decompressed_data_size);
}

bool CpuSmash::GetCompressionLevelInformation(
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  return lib->GetCompressionLevelInformation(compression_level_information,
                                             minimum_level, maximum_level);
}

bool CpuSmash::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  return lib->GetWindowSizeInformation(window_size_information, minimum_size,
                                       maximum_size);
}

bool CpuSmash::GetModeInformation(std::vector<std::string> *mode_information,
                                  uint8_t *minimum_mode, uint8_t *maximum_mode,
                                  const uint8_t &compression_level) {
  return lib->GetModeInformation(mode_information, minimum_mode, maximum_mode,
                                 compression_level);
}

bool CpuSmash::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information, uint8_t *minimum_factor,
    uint8_t *maximum_factor) {
  return lib->GetWorkFactorInformation(work_factor_information, minimum_factor,
                                       maximum_factor);
}

bool CpuSmash::GetFlagsInformation(std::vector<std::string> *flags_information,
                                   uint8_t *minimum_flags,
                                   uint8_t *maximum_flags) {
  return lib->GetFlagsInformation(flags_information, minimum_flags,
                                  maximum_flags);
}

bool CpuSmash::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  return lib->GetNumberThreadsInformation(number_threads_information,
                                          minimum_threads, maximum_threads);
}

bool CpuSmash::GetBackReferenceInformation(
    std::vector<std::string> *back_reference_information,
    uint8_t *minimum_back_reference, uint8_t *maximum_back_reference) {
  return lib->GetBackReferenceInformation(back_reference_information,
                                          minimum_back_reference,
                                          maximum_back_reference);
}

std::string CpuSmash::GetModeName(const uint8_t &mode) {
  return lib->GetModeName(mode);
}

std::string CpuSmash::GetFlagsName(const uint8_t &flags) {
  return lib->GetFlagsName(flags);
}

CpuOptions CpuSmash::GetOptions() { return lib->GetOptions(); }

CpuSmash::CpuSmash(const std::string &compression_library_name) {
  lib =
      CpuCompressionLibraries().GetCompressionLibrary(compression_library_name);
}

CpuSmash::~CpuSmash() { delete lib; }
