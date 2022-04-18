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
#include <network_server.hpp>
#include <options.hpp>
#include <result.hpp>
#include <smash.hpp>
#include <utils.hpp>

bool SetUnpackedMemory(char **data, uint64_t *size, NetworkServer *net) {
  bool result{true};
  result = net->RecvBuffer(reinterpret_cast<char *>(size), sizeof(*size));
  if (result) {
    *data = new char[*size];
    result = net->RecvBuffer(*data, *size);
  }
  return result;
}

bool SetMemories(char **uncompressed_data, uint64_t *uncompressed_size,
                 char **compressed_data, uint64_t *compressed_size,
                 char **decompressed_data, uint64_t *decompressed_size,
                 NetworkServer *net) {
  bool result = SetUnpackedMemory(uncompressed_data, uncompressed_size, net);
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

bool RecvInformationFromClient(Options *options, std::string *library_name,
                               bool *all_options, uint8_t *best_options,
                               uint32_t *best_result_number,
                               uint32_t *repetitions, NetworkServer *net) {
  bool status{true};
  status = net->RecvBuffer(reinterpret_cast<char *>(options), sizeof(*options));
  if (status) {
    uint8_t len{0};
    status = net->RecvBuffer(reinterpret_cast<char *>(&len), sizeof(len));
    if (status) {
      char name_aux[len + 1];  // NOLINT
      name_aux[len] = '\0';
      status = net->RecvBuffer(name_aux, len);
      *library_name = name_aux;
      if (status) {
        status = net->RecvBuffer(reinterpret_cast<char *>(all_options),
                                 sizeof(*all_options));
        if (status) {
          status = net->RecvBuffer(reinterpret_cast<char *>(best_options),
                                   sizeof(*best_options));
          if (status) {
            status =
                net->RecvBuffer(reinterpret_cast<char *>(best_result_number),
                                sizeof(*best_result_number));
            if (status) {
              status = net->RecvBuffer(reinterpret_cast<char *>(repetitions),
                                       sizeof(*repetitions));
            }
          }
        }
      }
    }
  }
  return status;
}

int main(int argc, char *argv[]) {
  Options opt;
  Smash *lib;
  std::string compression_library_name;
  uint64_t uncompressed_size{0};
  std::vector<Options> options;
  std::vector<Result> results;
  uint8_t best_options{0};
  uint32_t best_result_number{0};
  uint32_t repetitions{1};
  bool all_options{false};
  int result{EXIT_FAILURE};
  int port{-1};
  NetworkServer *net{nullptr};
  if (Utils::GetParamsServer(argc, argv, &port)) {
    net = new NetworkServer();
    result = net->InitializeServer(port) ? EXIT_SUCCESS : EXIT_FAILURE;
    if (result == EXIT_SUCCESS) {
      while (true) {
        result = net->GetNewConnection() ? EXIT_SUCCESS : EXIT_FAILURE;
        if (result == EXIT_SUCCESS) {
          if (RecvInformationFromClient(
                  &opt, &compression_library_name, &all_options, &best_options,
                  &best_result_number, &repetitions, net)) {
            std::vector<std::string> libraries =
                GetLibraries(compression_library_name);
            for (auto &library_name : libraries) {
              lib = new Smash(library_name);
              options = GetOptions(opt, all_options, lib);
              for (auto &option : options) {
                char *uncompressed_data{nullptr}, *compressed_data{nullptr},
                    *decompressed_data{nullptr};
                uint64_t compressed_size{0}, decompressed_size{0};
                if (SetMemories(&uncompressed_data, &uncompressed_size,
                                &compressed_data, &compressed_size,
                                &decompressed_data, &decompressed_size, net)) {
                  result = EXIT_SUCCESS;
                  for (uint32_t r = 0;
                       r < repetitions && result == EXIT_SUCCESS; ++r) {
                    std::chrono::_V2::system_clock::time_point start;
                    std::chrono::duration<double> decompression_time;
                    // Receive Compressed Data
                    // First, data size is received
                    result = net->RecvBuffer(
                                 reinterpret_cast<char *>(&compressed_size),
                                 sizeof(compressed_size))
                                 ? EXIT_SUCCESS
                                 : EXIT_FAILURE;
                    if (result == EXIT_SUCCESS) {
                      // Second, the data is received
                      result = net->RecvBuffer(compressed_data, compressed_size,
                                               true)
                                   ? EXIT_SUCCESS
                                   : EXIT_FAILURE;
                      if (result == EXIT_SUCCESS) {
                        // Set Decompression Options
                        result = lib->SetOptionsDecompressor(&option)
                                     ? EXIT_SUCCESS
                                     : EXIT_FAILURE;
                        if (result == EXIT_SUCCESS) {
                          InitializeTime(&start);
                          // Compress Data
                          result = lib->Decompress(
                                       compressed_data, compressed_size,
                                       decompressed_data, &decompressed_size)
                                       ? EXIT_SUCCESS
                                       : EXIT_FAILURE;
                          GetDuration(start, &decompression_time);
                          if (result == EXIT_SUCCESS) {
                            if (lib->CompareData(
                                    uncompressed_data, uncompressed_size,
                                    decompressed_data, decompressed_size)) {
                              net->SendACK(true);
                              double dec_time = decompression_time.count();
                              net->SendBuffer(
                                  reinterpret_cast<char *>(&dec_time),
                                  sizeof(dec_time));
                            } else {
                              std::cout << "ERROR: " << library_name
                                        << " does not obtain the correct data"
                                        << std::endl;
                              result = EXIT_FAILURE;
                              net->SendACK(false);
                            }
                          } else {
                            std::cout << "ERROR: " << library_name
                                      << " does not obtain the correct data"
                                      << std::endl;
                          }
                        } else {
                          std::cout << "ERROR: " << library_name
                                    << " does not set options correctly"
                                    << std::endl;
                        }
                      } else {
                        std::cout << "ERROR: " << library_name
                                  << " when data is transfered" << std::endl;
                      }
                    } else {
                      std::cout << "ERROR: " << library_name
                                << " when data is transfered" << std::endl;
                    }
                  }
                }
                RemoveMemories(uncompressed_data, compressed_data,
                               decompressed_data);
              }
              delete lib;
            }
          } else {
            std::cout << "Error receiving options from client" << std::endl;
            result = EXIT_FAILURE;
          }
        } else {
          std::cout << "Error taking a new connection" << std::endl;
        }
      }
    } else {
      std::cout << "Error initializing server" << std::endl;
    }
    delete net;
  }
  return result;
}
