/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

// SMASH LIBRARIES
#include <compression_libraries.hpp>
#include <smash.hpp>

bool Smash::SetOptions(Options options) { return lib->SetOptions(options); }

void Smash::GetCompressedDataSize(uint64_t uncompressed_size,
                                  uint64_t *compressed_size) {
  lib->GetCompressedDataSize(uncompressed_size, compressed_size);
}

void Smash::Compress(char *uncompressed_data, uint64_t uncompressed_size,
                     char *compressed_data, uint64_t *compressed_size) {
  lib->Compress(uncompressed_data, uncompressed_size, compressed_data,
                compressed_size);
}

void Smash::GetDecompressedDataSize(char *compressed_data,
                                    uint64_t compressed_size,
                                    uint64_t *decompressed_size) {
  lib->GetDecompressedDataSize(compressed_data, compressed_size,
                               decompressed_size);
}

void Smash::Decompress(char *compressed_data, uint64_t compressed_size,
                       char *decompressed_data, uint64_t *decompressed_size) {
  lib->Decompress(compressed_data, compressed_size, decompressed_data,
                  decompressed_size);
}

void Smash::GetTitle() { lib->GetTitle(); }

bool Smash::CompareData(char *uncompressed_data,
                        const uint64_t &uncompressed_size,
                        char *decompressed_data,
                        const uint64_t &decompressed_size) {
  return lib->CompareData(uncompressed_data, uncompressed_size,
                          decompressed_data, decompressed_size);
}

bool Smash::GetCompressionLevelInformation(
    uint8_t *minimum_level, uint8_t *maximum_level,
    std::vector<std::string> *compression_level_information) {
  return lib->GetCompressionLevelInformation(minimum_level, maximum_level,
                                             compression_level_information);
}

bool Smash::GetWindowSizeInformation(
    uint32_t *minimum_size, uint32_t *maximum_size,
    std::vector<std::string> *window_size_information) {
  return lib->GetWindowSizeInformation(minimum_size, maximum_size,
                                       window_size_information);
}

bool Smash::GetModeInformation(uint8_t *minimum_mode, uint8_t *maximum_mode,
                               std::vector<std::string> *mode_information) {
  return lib->GetModeInformation(minimum_mode, maximum_mode, mode_information);
}

bool Smash::GetWorkFactorInformation(
    uint8_t *minimum_factor, uint8_t *maximum_factor,
    std::vector<std::string> *work_factor_information) {
  return lib->GetWorkFactorInformation(minimum_factor, maximum_factor,
                                       work_factor_information);
}

bool Smash::GetShuffleInformation(
    uint8_t *minimum_shuffle, uint8_t *maximum_shuffle,
    std::vector<std::string> *shuffle_information) {
  return lib->GetShuffleInformation(minimum_shuffle, maximum_shuffle,
                                    shuffle_information);
}

bool Smash::GetNumberThreadsInformation(
    uint8_t *minimum_threads, uint8_t *maximum_threads,
    std::vector<std::string> *number_threads_information) {
  return lib->GetNumberThreadsInformation(minimum_threads, maximum_threads,
                                          number_threads_information);
}

bool Smash::GetBackReferenceBitsInformation(
    uint8_t *minimum_bits, uint8_t *maximum_bits,
    std::vector<std::string> *back_reference_information) {
  return lib->GetBackReferenceBitsInformation(minimum_bits, maximum_bits,
                                              back_reference_information);
}

std::string Smash::GetModeName(const uint8_t &mode) {
  return lib->GetModeName(mode);
}

std::string Smash::GetShuffleName(const uint8_t &shuffle) {
  return lib->GetShuffleName(shuffle);
}

Smash::Smash(const std::string &compression_library_name) {
  lib = CompressionLibraries().GetCompressionLibrary(compression_library_name);
}

Smash::~Smash() { delete lib; }
