/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <string.h>

#include <chrono>  // NOLINT
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

// SMASH LIBRARIES
#include <compression_libraries.hpp>
#include <options.hpp>
#include <smash.hpp>

const uint16_t val_name = 45;
const uint16_t val_description = 60;

void printLineRecursive() { std::cout << std::endl; }

template <typename... Strings>
void printLineRecursive(std::string r_message, const Strings &...args) {
  std::cout << std::left << std::setw(val_description) << std::setfill(' ')
            << r_message.substr(0, val_description);
  std::cout << std::endl;
  while (val_description < r_message.size()) {
    r_message = r_message.substr(val_description);
    std::cout << std::left << std::setw(val_name) << std::setfill(' ') << " ";
    std::cout << std::left << std::setw(val_description) << std::setfill(' ')
              << r_message.substr(0, val_description);
    std::cout << std::endl;
  }
  std::cout << std::left << std::setw(val_name) << std::setfill(' ') << " ";
  printLineRecursive(args...);
}

template <typename... Strings>
void printLine(std::string l_message, std::string r_message,
               const Strings &...args) {
  std::cout << std::left << std::setw(val_name) << std::setfill(' ')
            << " " + l_message;
  printLineRecursive(r_message, args...);
}

void showMessage(const std::string &exe) {
  std::cout << "To run the smash benchmark: " << std::endl;
  std::cout << " " << exe << " -c <library_name> -f <name_file>";
  std::cout << " [-o <output_name_file>]" << std::endl << std::endl;
  std::cout << "Arguments availables:" << std::endl << std::endl;
  printLine("-h, --help", "Show this message");
  printLine("-a, --available_libraries",
            "Show a list of the available libraries");
  printLine("-i, --information <library_name>",
            "Show information about a specific library");
  printLine("-c, --compression_library <library_name>",
            "Library name to use in compression/decompression");
  printLine("-f, --file <file_name>", "File name to compress");
  printLine("-o, --output_file <file_name>",
            "File name where the compress data is stored");
  printLine("-l, --level <number>", "Compression level to use (1 by default)");
  printLine("-w, --window <number>", "Set window size",
            "Values depend of different libraries (10 by default)");
  printLine("-m, --mode <number>", "Specifies the input type (0 by default)",
            "0: Generic", "1: UTF-8 formatted text input",
            "2: Web Open Font Format input");
  printLine("-wf, --work_factor <number>",
            "Controls how the compression works with repetitive data",
            "Values depend of different libraries (30 by default)");
  printLine("-s, --shuffle <number>", "Shuffle filter applied (0 by default)",
            "0: No Shuffle", "1: Byte Shuffle", "2: Bit Shuffle");
  printLine("-t, --threads <number>",
            "Threads used in algorithms (1 by default)",
            "Not all compression libraries use it");
}

void listCompressionLibraries() {
  std::cout << "Available compression libraries:" << std::endl << std::endl;
  CompressionLibraries().getListInformation();
}

bool check(const char *const param, const char *const first_value,
           const char *const second_value) {
  return (strcmp(param, first_value) == 0) | (strcmp(param, second_value) == 0);
}

void showLibraryInformation(const std::string &library_name,
                            const std::string &exe) {
  // TODO(Cristian): Must show the information of the especific library
}

bool getParams(const int &number_params, const char *const params[],
               Options *opt, std::string *input_file_name,
               std::string *output_file_name,
               std::string *compression_library_name) {
  bool show_message{true};
  bool end{false};
  bool error{false};
  bool compression_level_set{false};
  bool window_size_set{false};
  bool mode_set{false};
  bool work_factor_set{false};
  bool shuffle_set{false};
  bool threads_set{false};

  for (int n = 1; n < number_params && !end; ++n) {
    if (check(params[n], "-h", "--help")) {
      showMessage(params[0]);
      exit(EXIT_SUCCESS);
    } else if (check(params[n], "-a", "--available_libraries")) {
      listCompressionLibraries();
      exit(EXIT_SUCCESS);
    } else if (check(params[n], "-i", "--information")) {
      ++n;
      if (n < number_params) {
        showLibraryInformation(params[n], params[0]);
        exit(EXIT_SUCCESS);
      } else {
        error = true;
      }
      end = true;
    } else if (check(params[n], "-c", "--compression_library")) {
      ++n;
      if (n < number_params && compression_library_name->empty()) {
        *compression_library_name = params[n];
      } else {
        error = end = true;
      }
    } else if (check(params[n], "-f", "--file")) {
      ++n;
      if (n < number_params && input_file_name->empty()) {
        *input_file_name = params[n];
      } else {
        error = end = true;
      }
    } else if (check(params[n], "-o", "--output_file")) {
      ++n;
      if (n < number_params && output_file_name->empty()) {
        *output_file_name = params[n];
      } else {
        error = end = true;
      }
    } else if (check(params[n], "-l", "--level")) {
      ++n;
      if (n < number_params && !compression_level_set) {
        opt->setCompressionLevel(atoi(params[n]));
        compression_level_set = true;
      } else {
        error = end = true;
      }
    } else if (check(params[n], "-w", "--window")) {
      ++n;
      if (n < number_params && !window_size_set) {
        opt->setWindowSize(atoi(params[n]));
        window_size_set = true;
      } else {
        error = end = true;
      }
    } else if (check(params[n], "-m", "--mode")) {
      ++n;
      if (n < number_params && !mode_set) {
        opt->setMode(atoi(params[n]));
        mode_set = true;
      } else {
        error = end = true;
      }
    } else if (check(params[n], "-wf", "--work_factor")) {
      ++n;
      if (n < number_params && !work_factor_set) {
        opt->setWorkFactor(atoi(params[n]));
        work_factor_set = true;
      } else {
        error = end = true;
      }
    } else if (check(params[n], "-s", "--shuffle")) {
      ++n;
      if (n < number_params && !shuffle_set) {
        opt->setShuffle(atoi(params[n]));
        shuffle_set = true;
      } else {
        error = end = true;
      }
    } else if (check(params[n], "-t", "--threads")) {
      ++n;
      if (n < number_params && !threads_set) {
        opt->setNumberThreads(atoi(params[n]));
        threads_set = true;
      } else {
        error = end = true;
      }
    } else {
      error = end = true;
    }
  }

  if (error) {
    std::cout << "ERROR: Wrong arguments" << std::endl << std::endl;
    showMessage(params[0]);
    exit(EXIT_FAILURE);
  }

  show_message = compression_library_name->empty() || input_file_name->empty();

  if (show_message) {
    std::cout << "ERROR: Not enought arguments" << std::endl << std::endl;
    showMessage(params[0]);
    exit(EXIT_FAILURE);
  }
  return !show_message || !end;
}

bool setUnpackedMemory(std::string input_file_name, char **data,
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

bool copyToFile(std::string output_file_name, char *data, uint64_t size) {
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

bool setMemories(std::string input_file_name, char **uncompressed_data,
                 uint64_t *uncompressed_size, char **compressed_data,
                 uint64_t *compressed_size, char **decompressed_data,
                 uint64_t *decompressed_size) {
  bool result =
      setUnpackedMemory(input_file_name, uncompressed_data, uncompressed_size);

  *compressed_size = *uncompressed_size + 5000;
  *compressed_data = new char[*compressed_size];

  *decompressed_size = *uncompressed_size;
  *decompressed_data = new char[*decompressed_size];

  return result;
}

void removeMemories(char *uncompressed_data, char *compressed_data,
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

const uint16_t size_rows = 17;
void showTitle() {
  std::cout << std::left << std::setw(size_rows) << std::setfill(' ')
            << "| Library";
  std::cout << std::left << std::setw(size_rows) << std::setfill(' ')
            << "| Original data";
  std::cout << std::left << std::setw(size_rows) << std::setfill(' ')
            << "| Packed data";
  std::cout << std::left << std::setw(size_rows) << std::setfill(' ')
            << "| Ratio";
  std::cout << std::left << std::setw(size_rows) << std::setfill(' ')
            << "| Compress";
  std::cout << std::left << std::setw(size_rows) << std::setfill(' ')
            << "| Decompress";
  std::cout << std::left << std::setw(size_rows) << std::setfill(' ')
            << "| Total"
            << "|";
  std::cout << std::endl;
  std::cout << std::left << std::setw(size_rows * 7 + 1) << std::setfill('-')
            << "-" << std::endl;
}

void showResult(const std::string &library_name, Options opt,
                const uint64_t &uncompressed_size,
                const uint64_t &compressed_size, const double &time_compression,
                const double &time_decompression) {
  double vel_compression =
      ((static_cast<double>(uncompressed_size) / 1000000.0) / time_compression);
  double vel_decompression =
      ((static_cast<double>(compressed_size) / 1000000.0) / time_decompression);
  double vel_total = ((static_cast<double>(uncompressed_size) / 1000000.0) /
                      (time_compression + time_decompression));

  std::cout << std::left << std::setw(size_rows) << std::setfill(' ')
            << "| " + library_name;
  std::cout << std::left << std::setw(size_rows) << std::setfill(' ')
            << "| " + std::to_string(uncompressed_size) + " Bytes";

  std::cout << std::left << std::setw(size_rows) << std::setfill(' ')
            << "| " + std::to_string(compressed_size) + " Bytes";
  std::cout << std::left << std::setw(size_rows) << std::setfill(' ')
            << "| " + std::to_string((static_cast<double>(uncompressed_size) /
                                      static_cast<double>(compressed_size)));
  std::cout << std::left << std::setw(size_rows) << std::setfill(' ')
            << "| " + std::to_string(vel_compression) + " MB/s";
  std::cout << std::left << std::setw(size_rows) << std::setfill(' ')
            << "| " + std::to_string(vel_decompression) + " MB/s";
  std::cout << std::left << std::setw(size_rows) << std::setfill(' ')
            << "| " + std::to_string(vel_total) + " MB/s"
            << "|";
  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  Options opt;
  Smash *lib;
  std::string input_file_name;
  std::string output_file_name;
  std::string compression_library_name;
  int result{EXIT_FAILURE};

  if (getParams(argc, argv, &opt, &input_file_name, &output_file_name,
                &compression_library_name)) {
    showTitle();
    char *uncompressed_data{nullptr};
    char *compressed_data{nullptr};
    char *decompressed_data{nullptr};
    uint64_t uncompressed_size{0};
    uint64_t compressed_size{0};
    uint64_t decompressed_size{0};
    if (setMemories(input_file_name, &uncompressed_data, &uncompressed_size,
                    &compressed_data, &compressed_size, &decompressed_data,
                    &decompressed_size)) {
      result = EXIT_SUCCESS;
      lib = new Smash(compression_library_name);
      lib->getCompressDataSize(uncompressed_size, &compressed_size);
      std::chrono::_V2::system_clock::time_point start, end;
      std::chrono::duration<double> compression_time, decompression_time;

      start = std::chrono::system_clock::now();
      lib->compress(opt, uncompressed_data, uncompressed_size, compressed_data,
                    &compressed_size);
      end = std::chrono::system_clock::now();
      compression_time = end - start;

      start = std::chrono::system_clock::now();
      lib->decompress(compressed_data, compressed_size, decompressed_data,
                      &decompressed_size);
      end = std::chrono::system_clock::now();
      decompression_time = end - start;

      if (!lib->compareData(uncompressed_data, uncompressed_size,
                            decompressed_data, decompressed_size)) {
        std::cout << "ERROR: " << compression_library_name
                  << " does not obtain the correct data" << std::endl;
        result = EXIT_FAILURE;
      } else {
        if (copyToFile(output_file_name, compressed_data, compressed_size)) {
          showResult(compression_library_name, opt, uncompressed_size,
                     compressed_size, compression_time.count(),
                     decompression_time.count());
          result = EXIT_SUCCESS;
        } else {
          result = EXIT_FAILURE;
        }
      }
    }
    removeMemories(uncompressed_data, compressed_data, decompressed_data);
  }
  return result;
}
