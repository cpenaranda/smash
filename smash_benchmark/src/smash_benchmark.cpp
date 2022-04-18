/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <math.h>
#include <string.h>

#include <algorithm>
#include <chrono>  // NOLINT
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

// SMASH LIBRARIES
#include <compression_libraries.hpp>
#include <options.hpp>
#include <result.hpp>
#include <smash.hpp>
#include <utils.hpp>

bool SetUnpackedMemory(std::string input_file_name, char **data,
                       uint64_t *size) {
  bool result{true};
  std::ifstream src(input_file_name, std::ios::binary);
  if (!src.is_open()) {
    std::cout << "ERROR: The file does not exists" << std::endl;
    result = false;
  } else {
    src.seekg(0, std::ios::end);
    *size = src.tellg();
    src.seekg(0, std::ios::beg);

    *data = new char[*size];
    src.read(*data, *size);
    src.close();
  }
  return result;
}

bool CopyToFile(std::string output_file_name, char *data, uint64_t size) {
  bool result{true};
  if (!output_file_name.empty()) {
    std::ofstream dst(output_file_name, std::ios::binary);
    if (!dst.is_open()) {
      std::cout << "The packed file can not be created" << std::endl;
      result = false;
    }
    dst.write(data, size);
    dst.close();
  }
  return result;
}

bool SetMemories(std::string input_file_name, char **uncompressed_data,
                 uint64_t *uncompressed_size, char **compressed_data,
                 uint64_t *compressed_size, char **decompressed_data,
                 uint64_t *decompressed_size) {
  bool result =
      SetUnpackedMemory(input_file_name, uncompressed_data, uncompressed_size);

  if (*uncompressed_size < 2500) {
    *compressed_size = 5000;
  } else {
    *compressed_size = *uncompressed_size * 2;
  }
  *compressed_data = new char[*compressed_size];
  memset(*compressed_data, '\0', sizeof(char) * (*compressed_size));

  *decompressed_size = *uncompressed_size;
  *decompressed_data = new char[*decompressed_size];
  memset(*decompressed_data, '\0', sizeof(char) * (*decompressed_size));

  return result;
}

void RemoveMemories(char *uncompressed_data, char *compressed_data,
                    char *decompressed_data) {
  if (uncompressed_data) {
    delete[] uncompressed_data;
    uncompressed_data = nullptr;
  }
  if (compressed_data) {
    delete[] compressed_data;
    compressed_data = nullptr;
  }
  if (decompressed_data) {
    delete[] decompressed_data;
    decompressed_data = nullptr;
  }
}

std::vector<std::string> GetLibraries(const std::string &library_name) {
  std::vector<std::string> libraries;
  if (!library_name.compare("all")) {
    libraries = CompressionLibraries().GetNameLibraries();
  } else {
    libraries.push_back(library_name);
  }
  return libraries;
}

std::vector<Options> GetOptions(const Options &option, const bool &all_options,
                                Smash *library) {
  std::vector<Options> options;
  if (all_options) {
    Utils::GetAllOptions(library, &options);
  } else {
    options.clear();
    options.push_back(option);
  }
  return options;
}

inline void InitializeTime(std::chrono::_V2::system_clock::time_point *start) {
  *start = std::chrono::system_clock::now();
}

inline void GetDuration(const std::chrono::_V2::system_clock::time_point &start,
                        std::chrono::duration<double> *time) {
  std::chrono::_V2::system_clock::time_point end =
      std::chrono::system_clock::now();
  *time = end - start;
}

void GetInformation(const uint32_t &repetitions,
                    std::vector<double> compression_results,
                    std::vector<double> decompression_results,
                    std::vector<double> total_results, double *mean_compression,
                    double *mean_decompression, double *mean_total,
                    double *error_compression, double *error_decompression,
                    double *error_total) {
  sort(compression_results.begin(), compression_results.end(),
       [](double &x, double &y) { return x > y; });
  sort(decompression_results.begin(), decompression_results.end(),
       [](double &x, double &y) { return x > y; });
  sort(total_results.begin(), total_results.end(),
       [](double &x, double &y) { return x > y; });
  if (repetitions > 1) {
    uint32_t i = 0;
    // All results are added up discarding 20%
    for (; (i < (compression_results.size() / 1.2)) ||
           ((compression_results.size() == 1) && (i == 0));
         ++i) {
      *mean_compression += compression_results[i];
      *mean_decompression += decompression_results[i];
      *mean_total += total_results[i];
    }
    // The means are obtained
    *mean_compression /= i;
    *mean_decompression /= i;
    *mean_total /= i;
    // First step to obtain typical deviation
    for (uint32_t j = 0; j < i; ++j) {
      *error_compression +=
          pow((compression_results[j] - *mean_compression), 2);
      *error_decompression +=
          pow((decompression_results[j] - *mean_decompression), 2);
      *error_total += pow((total_results[j] - *mean_total), 2);
    }
    // Second step to obtain typical deviation
    --i;
    if (i > 0) {
      *error_compression = sqrt(*error_compression / i);
      *error_decompression = sqrt(*error_decompression / i);
      *error_total = sqrt(*error_total / i);
    }
  } else {
    *mean_compression += compression_results[0];
    *mean_decompression += decompression_results[0];
    *mean_total += total_results[0];
  }
}

int main(int argc, char *argv[]) {
  Options opt;
  Smash *lib;
  std::string input_file_name;
  std::string output_file_name;
  std::string compression_library_name;
  uint64_t uncompressed_size{0};
  std::vector<Options> options;
  std::vector<Result> results;
  uint8_t best_options{0};
  uint32_t best_result_number{0};
  uint32_t repetitions{1};
  bool all_options{false};
  int result{EXIT_FAILURE};
  if (Utils::GetParams(argc, argv, &opt, &input_file_name, &output_file_name,
                       &compression_library_name, &all_options, &best_options,
                       &best_result_number, &repetitions)) {
    std::vector<std::string> libraries = GetLibraries(compression_library_name);
    for (auto &library_name : libraries) {
      lib = new Smash(library_name);
      options = GetOptions(opt, all_options, lib);
      for (auto &option : options) {
        char *uncompressed_data{nullptr}, *compressed_data{nullptr},
            *decompressed_data{nullptr};
        uint64_t compressed_size{0}, decompressed_size{0};
        if (SetMemories(input_file_name, &uncompressed_data, &uncompressed_size,
                        &compressed_data, &compressed_size, &decompressed_data,
                        &decompressed_size)) {
          result = EXIT_SUCCESS;
          std::vector<double> compression_results, decompression_results,
              total_results;
          for (uint32_t r = 0; r < repetitions && result == EXIT_SUCCESS; ++r) {
            std::chrono::_V2::system_clock::time_point start;
            std::chrono::duration<double> compression_time, decompression_time;
            // Set Compression Options
            result = lib->SetOptionsCompressor(&option) ? EXIT_SUCCESS
                                                        : EXIT_FAILURE;
            // Get compressed Data Size
            lib->GetCompressedDataSize(uncompressed_data, uncompressed_size,
                                       &compressed_size);
            if (result == EXIT_SUCCESS) {
              InitializeTime(&start);
              // Compresss Data
              result = lib->Compress(uncompressed_data, uncompressed_size,
                                     compressed_data, &compressed_size)
                           ? EXIT_SUCCESS
                           : EXIT_FAILURE;
              GetDuration(start, &compression_time);
              if (result == EXIT_SUCCESS) {
                // Set Decompression Options
                result = lib->SetOptionsDecompressor(&option) ? EXIT_SUCCESS
                                                              : EXIT_FAILURE;
                if (result == EXIT_SUCCESS) {
                  InitializeTime(&start);
                  // Decompresss Data
                  result =
                      lib->Decompress(compressed_data, compressed_size,
                                      decompressed_data, &decompressed_size)
                          ? EXIT_SUCCESS
                          : EXIT_FAILURE;
                  GetDuration(start, &decompression_time);
                  if (result != EXIT_SUCCESS ||
                      !lib->CompareData(uncompressed_data, uncompressed_size,
                                        decompressed_data, decompressed_size)) {
                    std::cout << "ERROR: " << library_name
                              << " does not obtain the correct data"
                              << std::endl;
                    result = EXIT_FAILURE;
                  } else {
                    compression_results.push_back(
                        (static_cast<double>(uncompressed_size) / 1000000.0) /
                        compression_time.count());
                    decompression_results.push_back(
                        (static_cast<double>(compressed_size) / 1000000.0) /
                        decompression_time.count());
                    total_results.push_back(
                        (static_cast<double>(uncompressed_size) / 1000000.0) /
                        (compression_time.count() +
                         decompression_time.count()));
                  }
                } else {
                  std::cout << "ERROR: " << library_name
                            << " does not set options correctly" << std::endl;
                }
              } else {
                std::cout << "ERROR: " << library_name
                          << " does not obtain the correct data" << std::endl;
              }
            } else {
              std::cout << "ERROR: " << library_name
                        << " does not set options correctly" << std::endl;
            }
          }
          if (result == EXIT_SUCCESS) {
            double mean_compression{0}, mean_decompression{0}, mean_total{0},
                error_compression{0}, error_decompression{0}, error_total{0};

            GetInformation(repetitions, compression_results,
                           decompression_results, total_results,
                           &mean_compression, &mean_decompression, &mean_total,
                           &error_compression, &error_decompression,
                           &error_total);

            if (CopyToFile(output_file_name, compressed_data,
                           compressed_size)) {
              std::string message = Utils::ShowResult(
                  lib, library_name, uncompressed_size, compressed_size,
                  mean_compression, error_compression, mean_decompression,
                  error_decompression, mean_total, error_total);
              results.push_back(Result(
                  message, uncompressed_size, compressed_size, mean_compression,
                  mean_decompression, mean_total, best_options));
              result = EXIT_SUCCESS;
            } else {
              result = EXIT_FAILURE;
            }
          }
        }
        RemoveMemories(uncompressed_data, compressed_data, decompressed_data);
      }
      delete lib;
    }
    if (!results.empty()) {
      Utils::ShowTitle(uncompressed_size, repetitions);
      if (!best_options) {
        best_result_number = results.size();
      } else {
        std::sort(results.begin(), results.end());
      }
      while (best_result_number && !results.empty()) {
        std::cout << results.back().message_;
        results.pop_back();
        --best_result_number;
      }
    }
  }
  return result;
}
