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

void PrintLineRecursive() { std::cout << std::endl; }

void PrintDescription(std::string description) {
  while (val_description < description.size()) {
    std::cout << std::left << std::setw(val_name) << std::setfill(' ') << " ";
    std::cout << std::left << std::setw(val_description) << std::setfill(' ')
              << description.substr(0, val_description);
    std::cout << std::endl;
    description = description.substr(val_description);
  }
  std::cout << std::left << std::setw(val_name) << std::setfill(' ') << " ";
  std::cout << std::left << std::setw(val_description) << std::setfill(' ')
            << description.substr(0, val_description);
  std::cout << std::endl;
}

template <typename... Strings>
void PrintLineRecursive(std::string r_message, const Strings &...args) {
  std::cout << std::left << std::setw(val_description) << std::setfill(' ')
            << r_message.substr(0, val_description);
  std::cout << std::endl;
  if (val_description < r_message.size()) {
    r_message = r_message.substr(val_description);
    PrintDescription(r_message);
  }
  std::cout << std::left << std::setw(val_name) << std::setfill(' ') << " ";
  PrintLineRecursive(args...);
}

template <typename... Strings>
void PrintLine(std::string l_message, std::string r_message,
               const Strings &...args) {
  std::cout << std::left << std::setw(val_name) << std::setfill(' ')
            << " " + l_message;
  PrintLineRecursive(r_message, args...);
}

void PrintLine(std::string l_message, std::string r_message,
               std::vector<std::string> descriptions) {
  std::cout << std::left << std::setw(val_name) << std::setfill(' ')
            << " " + l_message;
  std::cout << std::left << std::setw(val_description) << std::setfill(' ')
            << r_message.substr(0, val_description);
  std::cout << std::endl;
  if (val_description < r_message.size()) {
    r_message = r_message.substr(val_description);
    PrintDescription(r_message);
  }
  for (auto &description : descriptions) {
    PrintDescription(description);
  }
  std::cout << std::endl;
}

void ShowMessage(const std::string &exe) {
  std::cout << "To run the specific library: " << std::endl;
  std::cout << " " << exe << " -c <library_name> -f <name_file>" << std::endl
            << std::endl;
  std::cout << "Arguments availables:" << std::endl << std::endl;
  PrintLine("-h, --help", "Show this message");
  PrintLine("-a, --available_libraries",
            "Show a list of the available libraries");
  PrintLine("-i, --information <library_name>",
            "Show information about a specific library");
  PrintLine("-c, --compression_library <library_name>",
            "Library name to use in compression/decompression");
  PrintLine("-f, --file <file_name>", "File name to compress");
  PrintLine("-o, --output_file <file_name>",
            "File name where the compress data is stored");
  PrintLine("-l, --level <number>", "Compression level to use",
            "Values depend of different libraries (1 by default)");
  PrintLine("-w, --window <number>", "Set window size",
            "Values depend of different libraries (10 by default)");
  PrintLine("-m, --mode <number>", "Specifies the mode used",
            "Values depend of different libraries (0 by default)");
  PrintLine("-wf, --work_factor <number>",
            "Controls how the compression works with repetitive data",
            "Values depend of different libraries (30 by default)");
  PrintLine("-s, --shuffle <number>", "Shuffle filter applied",
            "Values depend of different libraries (0 by default)");
  PrintLine("-t, --threads <number>",
            "Threads used in algorithms (1 by default)",
            "Not all compression libraries use it");
  PrintLine("-b, --back_reference_bits <number>",
            "Number of bits used for back-reference",
            "Values depend of different libraries (4 by default)");
}

void ListCompressionLibraries() {
  std::cout << "Available compression libraries:" << std::endl << std::endl;
  std::cout << std::left << std::setw(15) << std::setfill(' ') << "all"
            << "- "
            << "Run all the compression libraries with specific options"
            << std::endl;
  CompressionLibraries().GetListInformation();
}

bool Check(const char *const param, const char *const first_value,
           const char *const second_value) {
  return (strcmp(param, first_value) == 0) | (strcmp(param, second_value) == 0);
}

void ShowLibraryInformation(const std::string &library_name,
                            const std::string &exe) {
  std::vector<std::string> libraries;
  if (!library_name.compare("all")) {
    libraries = CompressionLibraries().GetNameLibraries();
  } else {
    libraries.push_back(library_name);
  }
  for (auto &lib_name : libraries) {
    Smash lib(lib_name);
    lib.GetTitle();
    std::cout << "To run the smash benchmark: " << std::endl;
    std::cout << " " << exe << " -c " << lib_name << " -f <name_file>"
              << std::endl
              << std::endl;
    PrintLine("-f, --file <file_name>", "File name to compress");
    PrintLine("-o, --output_file <file_name>",
              "File name where the compress data is stored");
    std::vector<std::string> information;
    lib.GetCompressionLevelInformation(nullptr, nullptr, &information);
    if (!information.empty()) {
      PrintLine("-l, --level <number>",
                "Compression level to use (1 by default)", information);
    }
    lib.GetWindowSizeInformation(nullptr, nullptr, &information);
    if (!information.empty()) {
      PrintLine("-w, --window <number>", "Set window size (10 by default)",
                information);
    }
    lib.GetModeInformation(nullptr, nullptr, &information);
    if (!information.empty()) {
      PrintLine("-m, --mode <number>", "Specifies the mode used (0 by default)",
                information);
    }
    lib.GetWorkFactorInformation(nullptr, nullptr, &information);
    if (!information.empty()) {
      PrintLine(
          "-wf, --work_factor <number>",
          "Controls how the compression works with repetitive data (30 by "
          "default)",
          information);
    }
    lib.GetShuffleInformation(nullptr, nullptr, &information);
    if (!information.empty()) {
      PrintLine("-s, --shuffle <number>",
                "Shuffle filter applied (0 by default)", information);
    }
    lib.GetNumberThreadsInformation(nullptr, nullptr, &information);
    if (!information.empty()) {
      PrintLine("-t, --threads <number>",
                "Threads used in algorithms (1 by default)", information);
    }
    lib.GetBackReferenceBitsInformation(nullptr, nullptr, &information);
    if (!information.empty()) {
      PrintLine("-b, --back_reference_bits <number>",
                "Number of bits used for back-reference (4 by default)",
                information);
    }
  }
}

bool GetParams(const int &number_params, const char *const params[],
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
  bool back_reference_bits_set{false};

  for (int n = 1; n < number_params && !end; ++n) {
    if (Check(params[n], "-h", "--help")) {
      ShowMessage(params[0]);
      exit(EXIT_SUCCESS);
    } else if (Check(params[n], "-a", "--available_libraries")) {
      ListCompressionLibraries();
      exit(EXIT_SUCCESS);
    } else if (Check(params[n], "-i", "--information")) {
      ++n;
      if (n < number_params) {
        ShowLibraryInformation(params[n], params[0]);
        exit(EXIT_SUCCESS);
      } else {
        error = true;
      }
      end = true;
    } else if (Check(params[n], "-c", "--compression_library")) {
      ++n;
      if (n < number_params && compression_library_name->empty()) {
        *compression_library_name = params[n];
      } else {
        error = end = true;
      }
    } else if (Check(params[n], "-f", "--file")) {
      ++n;
      if (n < number_params && input_file_name->empty()) {
        *input_file_name = params[n];
      } else {
        error = end = true;
      }
    } else if (Check(params[n], "-o", "--output_file")) {
      ++n;
      if (n < number_params && output_file_name->empty()) {
        *output_file_name = params[n];
      } else {
        error = end = true;
      }
    } else if (Check(params[n], "-l", "--level")) {
      ++n;
      if (n < number_params && !compression_level_set) {
        opt->SetCompressionLevel(atoi(params[n]));
        compression_level_set = true;
      } else {
        error = end = true;
      }
    } else if (Check(params[n], "-w", "--window")) {
      ++n;
      if (n < number_params && !window_size_set) {
        opt->SetWindowSize(atoi(params[n]));
        window_size_set = true;
      } else {
        error = end = true;
      }
    } else if (Check(params[n], "-m", "--mode")) {
      ++n;
      if (n < number_params && !mode_set) {
        opt->SetMode(atoi(params[n]));
        mode_set = true;
      } else {
        error = end = true;
      }
    } else if (Check(params[n], "-wf", "--work_factor")) {
      ++n;
      if (n < number_params && !work_factor_set) {
        opt->SetWorkFactor(atoi(params[n]));
        work_factor_set = true;
      } else {
        error = end = true;
      }
    } else if (Check(params[n], "-s", "--shuffle")) {
      ++n;
      if (n < number_params && !shuffle_set) {
        opt->SetShuffle(atoi(params[n]));
        shuffle_set = true;
      } else {
        error = end = true;
      }
    } else if (Check(params[n], "-t", "--threads")) {
      ++n;
      if (n < number_params && !threads_set) {
        opt->SetNumberThreads(atoi(params[n]));
        threads_set = true;
      } else {
        error = end = true;
      }
    } else if (Check(params[n], "-b", "--back_reference_bits")) {
      ++n;
      if (n < number_params && !back_reference_bits_set) {
        opt->SetBackReferenceBits(atoi(params[n]));
        back_reference_bits_set = true;
      } else {
        error = end = true;
      }
    } else {
      error = end = true;
    }
  }

  if (error) {
    std::cout << "ERROR: Wrong arguments" << std::endl << std::endl;
    ShowMessage(params[0]);
    exit(EXIT_FAILURE);
  }

  show_message = compression_library_name->empty() || input_file_name->empty();

  if (show_message) {
    std::cout << "ERROR: Not enought arguments" << std::endl << std::endl;
    ShowMessage(params[0]);
    exit(EXIT_FAILURE);
  }
  return !show_message || !end;
}

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

  *compressed_size = *uncompressed_size + 5000;
  *compressed_data = new char[*compressed_size];

  *decompressed_size = *uncompressed_size;
  *decompressed_data = new char[*decompressed_size];

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

const uint16_t size_rows = 17;
void ShowTitle() {
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

void ShowResult(const std::string &library_name, Options opt,
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

  if (GetParams(argc, argv, &opt, &input_file_name, &output_file_name,
                &compression_library_name)) {
    ShowTitle();
    std::vector<std::string> libraries;
    if (!compression_library_name.compare("all")) {
      libraries = CompressionLibraries().GetNameLibraries();
    } else {
      libraries.push_back(compression_library_name);
    }
    for (auto &library_name : libraries) {
      char *uncompressed_data{nullptr};
      char *compressed_data{nullptr};
      char *decompressed_data{nullptr};
      uint64_t uncompressed_size{0};
      uint64_t compressed_size{0};
      uint64_t decompressed_size{0};
      if (SetMemories(input_file_name, &uncompressed_data, &uncompressed_size,
                      &compressed_data, &compressed_size, &decompressed_data,
                      &decompressed_size)) {
        result = EXIT_SUCCESS;
        lib = new Smash(library_name);
        lib->GetCompressedDataSize(uncompressed_size, &compressed_size);
        std::chrono::_V2::system_clock::time_point start, end;
        std::chrono::duration<double> compression_time, decompression_time;
        lib->SetOptions(opt);
        start = std::chrono::system_clock::now();
        lib->Compress(uncompressed_data, uncompressed_size, compressed_data,
                      &compressed_size);
        end = std::chrono::system_clock::now();
        compression_time = end - start;

        start = std::chrono::system_clock::now();
        lib->Decompress(compressed_data, compressed_size, decompressed_data,
                        &decompressed_size);
        end = std::chrono::system_clock::now();
        decompression_time = end - start;

        if (!lib->CompareData(uncompressed_data, uncompressed_size,
                              decompressed_data, decompressed_size)) {
          std::cout << "ERROR: " << library_name
                    << " does not obtain the correct data" << std::endl;
          result = EXIT_FAILURE;
        } else {
          if (CopyToFile(output_file_name, compressed_data, compressed_size)) {
            ShowResult(library_name, opt, uncompressed_size,
                       compressed_size, compression_time.count(),
                       decompression_time.count());
            result = EXIT_SUCCESS;
          } else {
            result = EXIT_FAILURE;
          }
        }
      }
      RemoveMemories(uncompressed_data, compressed_data, decompressed_data);
    }
  }
  return result;
}
