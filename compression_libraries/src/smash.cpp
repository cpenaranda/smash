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
    std::vector<std::string> *compression_level_information,
    uint8_t *minimum_level, uint8_t *maximum_level) {
  return lib->GetCompressionLevelInformation(compression_level_information,
                                             minimum_level, maximum_level);
}

bool Smash::GetWindowSizeInformation(
    std::vector<std::string> *window_size_information, uint32_t *minimum_size,
    uint32_t *maximum_size) {
  return lib->GetWindowSizeInformation(window_size_information, minimum_size,
                                       maximum_size);
}

bool Smash::GetModeInformation(std::vector<std::string> *mode_information,
                               uint8_t *minimum_mode, uint8_t *maximum_mode) {
  return lib->GetModeInformation(mode_information, minimum_mode, maximum_mode);
}

bool Smash::GetWorkFactorInformation(
    std::vector<std::string> *work_factor_information,
    uint8_t *minimum_factor, uint8_t *maximum_factor) {
  return lib->GetWorkFactorInformation(work_factor_information, minimum_factor,
                                       maximum_factor);
}

bool Smash::GetShuffleInformation(
    std::vector<std::string> *shuffle_information,
    uint8_t *minimum_shuffle, uint8_t *maximum_shuffle) {
  return lib->GetShuffleInformation(shuffle_information, minimum_shuffle,
                                    maximum_shuffle);
}

bool Smash::GetNumberThreadsInformation(
    std::vector<std::string> *number_threads_information,
    uint8_t *minimum_threads, uint8_t *maximum_threads) {
  return lib->GetNumberThreadsInformation(number_threads_information,
                                          minimum_threads, maximum_threads);
}

bool Smash::GetBackReferenceBitsInformation(
    std::vector<std::string> *back_reference_information,
    uint8_t *minimum_bits, uint8_t *maximum_bits) {
  return lib->GetBackReferenceBitsInformation(back_reference_information,
                                              minimum_bits, maximum_bits);
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
