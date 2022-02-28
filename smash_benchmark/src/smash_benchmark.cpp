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
  std::cout << " " << exe << " -c <library_name> -i <name_file>" << std::endl
            << std::endl;
  std::cout << "Arguments availables:" << std::endl << std::endl;
  PrintLine("-h, --help", "Show this message");
  PrintLine("-h, --help <library_name>",
            "Show information about a specific library");
  PrintLine("-a, --available_libraries",
            "Show a list of the available libraries");
  PrintLine("-c, --compression_library <library_name>",
            "Library name to use in compression/decompression");
  PrintLine("-i, --input_file <file_name>", "File name to compress");
  PrintLine("-o, --output_file <file_name>",
            "File name where the compress data is stored");
  PrintLine("-e, --best_effort",
            "Run all possible configurations of the selected library");
  PrintLine("-n, --repetition_number <number>",
            "Compression and decompression are done <number> times",
            "(1 by default)");
  PrintLine(
      "-b, --best <option> <number>",
      "Get the <number> configurations of the selected library",
      "with the best <option>. Available options:", "0: Compression ratio",
      "1: Compression time", "2: Decompression time", "3: Total time");
  PrintLine("-l, --level <number>", "Compression level to use",
            "Values depend of different libraries (1 by default)");
  PrintLine("-s, --window_size <number>", "Set window size",
            "Values depend of different libraries (15 by default)");
  PrintLine("-m, --mode <number>", "Specifies the mode used",
            "Values depend of different libraries (0 by default)");
  PrintLine("-w, --work_factor <number>",
            "Controls how the compression works with repetitive data",
            "Values depend of different libraries (30 by default)");
  PrintLine("-f, --flags <number>", "Flags to use",
            "Values depend of different libraries (0 by default)");
  PrintLine("-r, --back_reference_bits <number>",
            "Number of bits used for back-reference",
            "Values depend of different libraries (4 by default)");
  PrintLine("-t, --threads <number>",
            "Threads used in algorithms (1 by default)",
            "Not all compression libraries use it");
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
    std::cout << " " << exe << " -c " << lib_name << " -i <name_file>"
              << std::endl
              << std::endl;
    PrintLine("-i, --input_file <file_name>", "File name to compress");
    PrintLine("-o, --output_file <file_name>",
              "File name where the compress data is stored");
    PrintLine("-n, --repetition_number <number>",
              "Compression and decompression are done <number> times",
              "(1 by default)");
    std::vector<std::string> information;
    lib.GetCompressionLevelInformation(&information);
    if (!information.empty()) {
      PrintLine("-l, --level <number>",
                "Compression level to use (1 by default)", information);
    }
    lib.GetWindowSizeInformation(&information);
    if (!information.empty()) {
      PrintLine("-s, --window_size <number>", "Set window size (15 by default)",
                information);
    }
    lib.GetModeInformation(&information);
    if (!information.empty()) {
      PrintLine("-m, --mode <number>", "Specifies the mode used (0 by default)",
                information);
    }
    lib.GetWorkFactorInformation(&information);
    if (!information.empty()) {
      PrintLine(
          "-w, --work_factor <number>",
          "Controls how the compression works with repetitive data (30 by "
          "default)",
          information);
    }
    lib.GetFlagsInformation(&information);
    if (!information.empty()) {
      PrintLine("-f, --flags <number>", "Flags to use (0 by default)",
                information);
    }
    lib.GetBackReferenceBitsInformation(&information);
    if (!information.empty()) {
      PrintLine("-r, --back_reference_bits <number>",
                "Number of bits used for back-reference (4 by default)",
                information);
    } else {
      std::cout << "ESTA VACIO" << std::endl;
    }
    lib.GetNumberThreadsInformation(&information);
    if (!information.empty()) {
      PrintLine("-t, --threads <number>",
                "Threads used in algorithms (1 by default)", information);
    }
  }
}

bool GetParams(const int &number_params, const char *const params[],
               Options *opt, std::string *input_file_name,
               std::string *output_file_name,
               std::string *compression_library_name, bool *all_options,
               uint8_t *option, uint32_t *result_number,
               uint32_t *repetitions) {
  bool show_message{true};
  bool end{false};
  bool error{false};
  bool compression_level_set{false};
  bool window_size_set{false};
  bool mode_set{false};
  bool work_factor_set{false};
  bool flags_set{false};
  bool threads_set{false};
  bool best_effort_set{false};
  bool best_set{false};
  bool back_reference_bits_set{false};
  bool repetitions_set{false};

  for (int n = 1; n < number_params && !end; ++n) {
    if (Check(params[n], "-h", "--help")) {
      if (n + 1 < number_params &&
          std::string(params[n + 1]).find("-") == std::string::npos) {
        ShowLibraryInformation(params[n + 1], params[0]);
      } else {
        ShowMessage(params[0]);
      }
      exit(EXIT_SUCCESS);
    } else if (Check(params[n], "-a", "--available_libraries")) {
      ListCompressionLibraries();
      exit(EXIT_SUCCESS);
    } else if (Check(params[n], "-c", "--compression_library")) {
      ++n;
      if (n < number_params && compression_library_name->empty()) {
        *compression_library_name = params[n];
      } else {
        error = end = true;
      }
    } else if (Check(params[n], "-i", "--input_file")) {
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
    } else if (Check(params[n], "-s", "--window_size")) {
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
    } else if (Check(params[n], "-w", "--work_factor")) {
      ++n;
      if (n < number_params && !work_factor_set) {
        opt->SetWorkFactor(atoi(params[n]));
        work_factor_set = true;
      } else {
        error = end = true;
      }
    } else if (Check(params[n], "-f", "--flags")) {
      ++n;
      if (n < number_params && !flags_set) {
        opt->SetFlags(atoi(params[n]));
        flags_set = true;
      } else {
        error = end = true;
      }
    } else if (Check(params[n], "-r", "--back_reference_bits")) {
      ++n;
      if (n < number_params && !back_reference_bits_set) {
        opt->SetBackReferenceBits(atoi(params[n]));
        back_reference_bits_set = true;
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
    } else if (Check(params[n], "-e", "--best_effort")) {
      if (!best_effort_set) {
        best_effort_set = true;
        *all_options = true;
      } else {
        error = end = true;
      }
    } else if (Check(params[n], "-b", "--best")) {
      ++n;
      if (n + 1 < number_params && !best_set) {
        best_set = true;
        *option = atoi(params[n]) + 1;
        if (*option > 4) {
          error = end = true;
        } else {
          ++n;
          *result_number = atoi(params[n]);
        }
      } else {
        error = end = true;
      }
    } else if (Check(params[n], "-n", "--repetition_number")) {
      ++n;
      if (n < number_params && !repetitions_set && atoi(params[n]) > 0) {
        repetitions_set = true;
        *repetitions = atoi(params[n]) * 1.2;
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

const uint16_t size_row_library = 13;
const uint16_t size_row_level = 8;
const uint16_t size_row_window = 9;
const uint16_t size_row_mode = 17;
const uint16_t size_row_factor = 6;
const uint16_t size_row_flags = 16;
const uint16_t size_row_threads = 10;
const uint16_t size_row_back_reference = 6;
const uint16_t size_rows_original_data = 16;
const uint16_t size_rows_packed_data = 14;
const uint16_t size_rows_ratio = 9;
const uint16_t size_rows_compress = 14;
const uint16_t size_rows_decompress = 14;
const uint16_t size_rows_total = 14;

void ShowTitle(const uint64_t &size, const uint64_t &repetitions) {
  *const_cast<uint16_t *>(&size_rows_original_data) =
      (size_rows_original_data < (std::to_string(size).size() + 9))
          ? std::to_string(size).size() + 9
          : size_rows_original_data;
  *const_cast<uint16_t *>(&size_rows_packed_data) =
      (size_rows_packed_data < (std::to_string(size).size() + 9))
          ? std::to_string(size).size() + 9
          : size_rows_packed_data;
  std::cout << std::left << std::setw(size_row_library) << std::setfill(' ')
            << "| Library";
  std::cout << std::left << std::setw(size_row_level) << std::setfill(' ')
            << "| Level";
  std::cout << std::left << std::setw(size_row_window) << std::setfill(' ')
            << "| Window";
  std::cout << std::left << std::setw(size_row_mode) << std::setfill(' ')
            << "| Mode";
  std::cout << std::left << std::setw(size_row_factor) << std::setfill(' ')
            << "| WF";
  std::cout << std::left << std::setw(size_row_flags) << std::setfill(' ')
            << "| Flags";
  std::cout << std::left << std::setw(size_row_threads) << std::setfill(' ')
            << "| Threads";
  std::cout << std::left << std::setw(size_row_back_reference)
            << std::setfill(' ') << "| BR";
  std::cout << std::left << std::setw(size_rows_original_data)
            << std::setfill(' ') << "| Original data";
  std::cout << std::left << std::setw(size_rows_packed_data)
            << std::setfill(' ') << "| Packed data";
  std::cout << std::left << std::setw(size_rows_ratio) << std::setfill(' ')
            << "| Ratio";
  std::cout << std::left << std::setw(size_rows_compress) << std::setfill(' ')
            << "| Compress";
  if (repetitions > 1) {
    std::cout << std::left << std::setw(size_rows_compress + 3)
              << std::setfill(' ') << "| Error Compress";
  }
  std::cout << std::left << std::setw(size_rows_decompress) << std::setfill(' ')
            << "| Decompress";
  if (repetitions > 1) {
    std::cout << std::left << std::setw(size_rows_compress + 5)
              << std::setfill(' ') << "| Error Decompress";
  }
  std::cout << std::left << std::setw(size_rows_total) << std::setfill(' ')
            << "| Total";
  if (repetitions > 1) {
    std::cout << std::left << std::setw(size_rows_compress) << std::setfill(' ')
              << "| Error Total";
  }
  std::cout << "|" << std::endl;

  std::cout << std::left
            << std::setw(size_row_library + size_row_level + size_row_window +
                         size_row_mode + size_row_factor + size_row_flags +
                         size_row_threads + size_row_back_reference +
                         size_rows_original_data + size_rows_packed_data +
                         size_rows_ratio + size_rows_compress +
                         size_rows_decompress + size_rows_total + 1 +
                         ((repetitions > 1)
                              ? size_rows_compress + size_rows_decompress +
                                    size_rows_total + 3 + 5
                              : 0))
            << std::setfill('-') << "-" << std::endl;
}

std::string ToStringDouble(const double &value) {
  std::ostringstream out;
  out.precision(2);
  out << std::fixed << value;
  return out.str();
}

std::string ShowResult(
    Smash *lib, const std::string &library_name, Options opt,
    const uint64_t &uncompressed_size, const uint64_t &compressed_size,
    const double &mean_vel_compression, const double &error_vel_compression,
    const double &mean_vel_decompression, const double &error_vel_decompression,
    const double &mean_vel_total, const double &error_vel_total) {
  std::ostringstream result;
  bool repetitions = error_vel_compression;
  result << std::left << std::setw(size_row_library) << std::setfill(' ')
         << "| " + library_name;

  if (lib->GetCompressionLevelInformation()) {
    result << std::left << std::setw(size_row_level) << std::setfill(' ')
           << "| " + std::to_string(opt.GetCompressionLevel());
  } else {
    result << std::left << std::setw(size_row_level - 1) << std::setfill('-')
           << "| "
           << " ";
  }

  if (lib->GetWindowSizeInformation()) {
    result << std::left << std::setw(size_row_window) << std::setfill(' ')
           << "| " + std::to_string(opt.GetWindowSize());
  } else {
    result << std::left << std::setw(size_row_window - 1) << std::setfill('-')
           << "| "
           << " ";
  }

  if (lib->GetModeInformation()) {
    result << std::left << std::setw(size_row_mode) << std::setfill(' ')
           << "| " + lib->GetModeName(opt.GetMode());
  } else {
    result << std::left << std::setw(size_row_mode - 1) << std::setfill('-')
           << "| "
           << " ";
  }

  if (lib->GetWorkFactorInformation()) {
    result << std::left << std::setw(size_row_factor) << std::setfill(' ')
           << "| " + std::to_string(opt.GetWorkFactor());
  } else {
    result << std::left << std::setw(size_row_factor - 1) << std::setfill('-')
           << "| "
           << " ";
  }

  if (lib->GetFlagsInformation()) {
    result << std::left << std::setw(size_row_flags) << std::setfill(' ')
           << "| " + lib->GetFlagsName(opt.GetFlags());
  } else {
    result << std::left << std::setw(size_row_flags - 1) << std::setfill('-')
           << "| "
           << " ";
  }

  if (lib->GetNumberThreadsInformation()) {
    result << std::left << std::setw(size_row_threads) << std::setfill(' ')
           << "| " + std::to_string(opt.GetNumberThreads());
  } else {
    result << std::left << std::setw(size_row_threads - 1) << std::setfill('-')
           << "| "
           << " ";
  }

  if (lib->GetBackReferenceBitsInformation()) {
    result << std::left << std::setw(size_row_back_reference)
           << std::setfill(' ')
           << "| " + std::to_string(opt.GetBackReferenceBits());
  } else {
    result << std::left << std::setw(size_row_back_reference - 1)
           << std::setfill('-') << "| "
           << " ";
  }

  result << std::left << std::setw(size_rows_original_data) << std::setfill(' ')
         << "| " + std::to_string(uncompressed_size) + " Bytes";

  result << std::left << std::setw(size_rows_packed_data) << std::setfill(' ')
         << "| " + std::to_string(compressed_size) + " Bytes";
  result << std::left << std::setw(size_rows_ratio) << std::setfill(' ')
         << "| " + ToStringDouble((static_cast<double>(uncompressed_size) /
                                   static_cast<double>(compressed_size)));

  result << std::left << std::setw(size_rows_compress) << std::setfill(' ')
         << "| " + ToStringDouble(mean_vel_compression) + " MB/s";
  if (repetitions) {
    result << std::left << std::setw(size_rows_compress + 3)
           << std::setfill(' ')
           << "| " + ToStringDouble(error_vel_compression) + " MB/s";
  }
  result << std::left << std::setw(size_rows_decompress) << std::setfill(' ')
         << "| " + ToStringDouble(mean_vel_decompression) + " MB/s";
  if (repetitions) {
    result << std::left << std::setw(size_rows_decompress + 5)
           << std::setfill(' ')
           << "| " + ToStringDouble(error_vel_decompression) + " MB/s";
  }
  result << std::left << std::setw(size_rows_total) << std::setfill(' ')
         << "| " + ToStringDouble(mean_vel_total) + " MB/s";
  if (repetitions) {
    result << std::left << std::setw(size_rows_total) << std::setfill(' ')
           << "| " + ToStringDouble(error_vel_total) + " MB/s";
  }

  result << "|" << std::endl;
  return result.str();
}

void SetNumberThreads(Smash *lib, std::vector<Options> *options,
                      Options *option) {
  uint8_t min_threads{0}, max_threads{0};
  bool set_value =
      lib->GetNumberThreadsInformation(nullptr, &min_threads, &max_threads);
  do {
    if (set_value) option->SetNumberThreads(min_threads);
    options->push_back(*option);
    ++min_threads;
  } while (min_threads <= max_threads);
}

void SetFlags(Smash *lib, std::vector<Options> *options, Options *option) {
  uint8_t min_flag{0}, max_flag{0};
  bool set_value = lib->GetFlagsInformation(nullptr, &min_flag, &max_flag);
  do {
    if (set_value) option->SetFlags(min_flag);
    SetNumberThreads(lib, options, option);
    ++min_flag;
  } while (min_flag <= max_flag);
}

void SetWorkFactor(Smash *lib, std::vector<Options> *options, Options *option) {
  uint8_t min_factor{0}, max_factor{0};
  bool set_value =
      lib->GetWorkFactorInformation(nullptr, &min_factor, &max_factor);
  do {
    if (set_value) option->SetWorkFactor(min_factor);
    SetFlags(lib, options, option);
    min_factor += 51;
  } while (min_factor <= max_factor);
}

void SetWindowSize(Smash *lib, std::vector<Options> *options, Options *option) {
  uint32_t min_window{0}, max_window{0};
  bool set_value =
      lib->GetWindowSizeInformation(nullptr, &min_window, &max_window);
  do {
    if (set_value) option->SetWindowSize(min_window);
    SetWorkFactor(lib, options, option);
    ++min_window;
  } while (min_window <= max_window);
}

void SetMode(Smash *lib, std::vector<Options> *options, Options *option,
             const uint8_t &level) {
  uint8_t min_mode{0}, max_mode{0};
  bool set_value =
      lib->GetModeInformation(nullptr, &min_mode, &max_mode, level);
  do {
    if (set_value) option->SetMode(min_mode);
    SetWindowSize(lib, options, option);
    ++min_mode;
  } while (min_mode <= max_mode);
}

void SetCopressionLevel(Smash *lib, std::vector<Options> *options) {
  Options option;
  uint8_t min_level{0}, max_level{0};
  bool set_value =
      lib->GetCompressionLevelInformation(nullptr, &min_level, &max_level);
  do {
    if (set_value) option.SetCompressionLevel(min_level);
    SetMode(lib, options, &option, min_level);
    ++min_level;
  } while (min_level <= max_level);
}

void GetAllOptions(Smash *lib, std::vector<Options> *options) {
  options->clear();
  SetCopressionLevel(lib, options);
}

struct Result {
  std::string message_;
  uint64_t uncompressed_size_;
  uint64_t compressed_size_;
  double compression_vel_;
  double decompression_vel_;
  double total_vel_;
  uint8_t option_;

  Result(const std::string &message, const uint64_t &uncompressed_size = 0,
         const uint64_t &compressed_size = 0, const double &compression_vel = 0,
         const double &decompression_vel = 0, const double &total_vel = 0,
         const uint8_t &option = 0) {
    message_ = message;
    uncompressed_size_ = uncompressed_size;
    compressed_size_ = compressed_size;
    compression_vel_ = compression_vel;
    decompression_vel_ = decompression_vel;
    total_vel_ = total_vel;
    option_ = option;
  }

  bool operator<(const Result &other) const {
    bool result{false};
    if (option_ == 1) {
      // Compression Ratio
      result = other.compressed_size_ < compressed_size_;
    } else if (option_ == 2) {
      if (other.compressed_size_ < other.uncompressed_size_) {
        // Compression Time
        result = other.compression_vel_ > compression_vel_;
      }
    } else if (option_ == 3) {
      if (other.compressed_size_ < other.uncompressed_size_) {
        // Decompression Time
        result = other.decompression_vel_ > decompression_vel_;
      }
    } else if (option_ == 4) {
      if (other.compressed_size_ < other.uncompressed_size_) {
        // Total Time
        result = other.total_vel_ > total_vel_;
      }
    }
    return result;
  }
};

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
  if (GetParams(argc, argv, &opt, &input_file_name, &output_file_name,
                &compression_library_name, &all_options, &best_options,
                &best_result_number, &repetitions)) {
    std::vector<std::string> libraries;
    if (!compression_library_name.compare("all")) {
      libraries = CompressionLibraries().GetNameLibraries();
    } else {
      libraries.push_back(compression_library_name);
    }
    options.push_back(opt);
    for (auto &library_name : libraries) {
      lib = new Smash(library_name);
      if (all_options) {
        GetAllOptions(lib, &options);
      }
      for (auto &option : options) {
        char *uncompressed_data{nullptr};
        char *compressed_data{nullptr};
        char *decompressed_data{nullptr};
        uint64_t compressed_size{0};
        uint64_t decompressed_size{0};
        if (SetMemories(input_file_name, &uncompressed_data, &uncompressed_size,
                        &compressed_data, &compressed_size, &decompressed_data,
                        &decompressed_size)) {
          result = EXIT_SUCCESS;
          std::vector<double> compression_results;
          std::vector<double> decompression_results;
          std::vector<double> total_results;
          for (uint32_t r = 0; r < repetitions && result == EXIT_SUCCESS; ++r) {
            lib->GetCompressedDataSize(uncompressed_data, uncompressed_size,
                                       &compressed_size);
            std::chrono::_V2::system_clock::time_point start, end;
            std::chrono::duration<double> compression_time, decompression_time;
            result =
                lib->SetOptionsCompressor(option) ? EXIT_SUCCESS : EXIT_FAILURE;
            if (result == EXIT_SUCCESS) {
              start = std::chrono::system_clock::now();
              result = lib->Compress(uncompressed_data, uncompressed_size,
                                     compressed_data, &compressed_size)
                           ? EXIT_SUCCESS
                           : EXIT_FAILURE;
              end = std::chrono::system_clock::now();
              compression_time = end - start;
              if (result == EXIT_SUCCESS) {
                result = lib->SetOptionsDecompressor(option) ? EXIT_SUCCESS
                                                             : EXIT_FAILURE;
                if (result == EXIT_SUCCESS) {
                  start = std::chrono::system_clock::now();
                  result =
                      lib->Decompress(compressed_data, compressed_size,
                                      decompressed_data, &decompressed_size)
                          ? EXIT_SUCCESS
                          : EXIT_FAILURE;
                  end = std::chrono::system_clock::now();
                  decompression_time = end - start;
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
                }
              }
            }
          }

          sort(compression_results.begin(), compression_results.end(),
               [](double &x, double &y) { return x > y; });
          sort(decompression_results.begin(), decompression_results.end(),
               [](double &x, double &y) { return x > y; });
          sort(total_results.begin(), total_results.end(),
               [](double &x, double &y) { return x > y; });

          double mean_compression{0}, mean_decompression{0}, mean_total{0},
              error_compression{0}, error_decompression{0}, error_total{0};
          if (repetitions > 1) {
            uint32_t i = 0;
            for (; (i < (compression_results.size() / 1.2)) ||
                   ((compression_results.size() == 1) && (i == 0));
                 ++i) {
              mean_compression += compression_results[i];
              mean_decompression += decompression_results[i];
              mean_total += total_results[i];
            }

            mean_compression /= i;
            mean_decompression /= i;
            mean_total /= i;

            for (uint32_t j = 0; j < i; ++j) {
              error_compression +=
                  pow((compression_results[j] - mean_compression), 2);
              error_decompression +=
                  pow((decompression_results[j] - mean_decompression), 2);
              error_total += pow((total_results[j] - mean_total), 2);
            }

            --i;
            if (i > 0) {
              error_compression = sqrt(error_compression / i);
              error_decompression = sqrt(error_decompression / i);
              error_total = sqrt(error_total / i);
            }
          } else {
            mean_compression += compression_results[0];
            mean_decompression += decompression_results[0];
            mean_total += total_results[0];
          }

          if (CopyToFile(output_file_name, compressed_data, compressed_size)) {
            std::string message = ShowResult(
                lib, library_name, option, uncompressed_size, compressed_size,
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
        RemoveMemories(uncompressed_data, compressed_data, decompressed_data);
      }
      delete lib;
    }
    if (!results.empty()) {
      ShowTitle(uncompressed_size, repetitions);
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
