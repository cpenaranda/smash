/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

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
  PrintLine("-b, --best_effort",
            "Run all possible configurations of the selected library");
  PrintLine(
      "-b, --best <option> <number>",
      "Get the <number> configurations of the selected library",
      "with the best <option>. Available options:", "0: Compression ratio",
      "1: Compression time", "2: Decompression time", "3: Total time");
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
    lib.GetCompressionLevelInformation(&information);
    if (!information.empty()) {
      PrintLine("-l, --level <number>",
                "Compression level to use (1 by default)", information);
    }
    lib.GetWindowSizeInformation(&information);
    if (!information.empty()) {
      PrintLine("-w, --window <number>", "Set window size (10 by default)",
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
          "-wf, --work_factor <number>",
          "Controls how the compression works with repetitive data (30 by "
          "default)",
          information);
    }
    lib.GetShuffleInformation(&information);
    if (!information.empty()) {
      PrintLine("-s, --shuffle <number>",
                "Shuffle filter applied (0 by default)", information);
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
               uint8_t *option, uint32_t *result_number) {
  bool show_message{true};
  bool end{false};
  bool error{false};
  bool compression_level_set{false};
  bool window_size_set{false};
  bool mode_set{false};
  bool work_factor_set{false};
  bool shuffle_set{false};
  bool threads_set{false};
  bool best_effort_set{false};
  bool best_set{false};

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
    } else if (!strcmp(params[n], "--best_effort")) {
      if (!best_effort_set) {
        best_effort_set = true;
        *all_options = true;
      } else {
        error = end = true;
      }
    } else if (!strcmp(params[n], "--best")) {
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
    } else if (!strcmp(params[n], "-b")) {
      if (n + 1 < number_params &&
          std::string(params[n + 1]).find("-") == std::string::npos) {
        if (n + 2 < number_params && !best_set) {
          ++n;
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
      } else {
        if (!best_effort_set) {
          best_effort_set = true;
          *all_options = true;
        } else {
          error = end = true;
        }
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
const uint16_t size_row_shuffle = 10;
const uint16_t size_row_threads = 10;
const uint16_t size_rows_original_data = 16;
const uint16_t size_rows_packed_data = 14;
const uint16_t size_rows_ratio = 9;
const uint16_t size_rows_compress = 14;
const uint16_t size_rows_decompress = 14;
const uint16_t size_rows_total = 14;

void ShowTitle(const uint64_t &size) {
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
  std::cout << std::left << std::setw(size_row_shuffle) << std::setfill(' ')
            << "| Shuffle";
  std::cout << std::left << std::setw(size_row_threads) << std::setfill(' ')
            << "| Threads";
  std::cout << std::left << std::setw(size_rows_original_data)
            << std::setfill(' ') << "| Original data";
  std::cout << std::left << std::setw(size_rows_packed_data)
            << std::setfill(' ') << "| Packed data";
  std::cout << std::left << std::setw(size_rows_ratio) << std::setfill(' ')
            << "| Ratio";
  std::cout << std::left << std::setw(size_rows_compress) << std::setfill(' ')
            << "| Compress";
  std::cout << std::left << std::setw(size_rows_decompress) << std::setfill(' ')
            << "| Decompress";
  std::cout << std::left << std::setw(size_rows_total) << std::setfill(' ')
            << "| Total"
            << "|";
  std::cout << std::endl;

  std::cout << std::left
            << std::setw(size_row_library + size_row_level + size_row_window +
                         size_row_mode + size_row_factor + size_row_shuffle +
                         size_row_threads + size_rows_original_data +
                         size_rows_packed_data + size_rows_ratio +
                         size_rows_compress + size_rows_decompress +
                         size_rows_total + 1)
            << std::setfill('-') << "-" << std::endl;
}

std::string ToStringDouble(const double &value) {
  std::ostringstream out;
  out.precision(2);
  out << std::fixed << value;
  return out.str();
}

std::string ShowResult(Smash *lib, const std::string &library_name, Options opt,
                       const uint64_t &uncompressed_size,
                       const uint64_t &compressed_size,
                       const double &time_compression,
                       const double &time_decompression) {
  std::ostringstream result;
  double vel_compression =
      ((static_cast<double>(uncompressed_size) / 1000000.0) / time_compression);
  double vel_decompression =
      ((static_cast<double>(compressed_size) / 1000000.0) / time_decompression);
  double vel_total = ((static_cast<double>(uncompressed_size) / 1000000.0) /
                      (time_compression + time_decompression));

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

  if (lib->GetShuffleInformation()) {
    result << std::left << std::setw(size_row_shuffle) << std::setfill(' ')
           << "| " + lib->GetShuffleName(opt.GetShuffle());
  } else {
    result << std::left << std::setw(size_row_shuffle - 1) << std::setfill('-')
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

  result << std::left << std::setw(size_rows_original_data) << std::setfill(' ')
         << "| " + std::to_string(uncompressed_size) + " Bytes";

  result << std::left << std::setw(size_rows_packed_data) << std::setfill(' ')
         << "| " + std::to_string(compressed_size) + " Bytes";
  result << std::left << std::setw(size_rows_ratio) << std::setfill(' ')
         << "| " + ToStringDouble((static_cast<double>(uncompressed_size) /
                                   static_cast<double>(compressed_size)));
  result << std::left << std::setw(size_rows_compress) << std::setfill(' ')
         << "| " + ToStringDouble(vel_compression) + " MB/s";
  result << std::left << std::setw(size_rows_decompress) << std::setfill(' ')
         << "| " + ToStringDouble(vel_decompression) + " MB/s";
  result << std::left << std::setw(size_rows_total) << std::setfill(' ')
         << "| " + ToStringDouble(vel_total) + " MB/s"
         << "|";
  result << std::endl;
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

void SetShuffle(Smash *lib, std::vector<Options> *options, Options *option) {
  uint8_t min_shuffle{0}, max_shuffle{0};
  bool set_value =
      lib->GetShuffleInformation(nullptr, &min_shuffle, &max_shuffle);
  do {
    if (set_value) option->SetShuffle(min_shuffle);
    SetNumberThreads(lib, options, option);
    ++min_shuffle;
  } while (min_shuffle <= max_shuffle);
}

void SetWorkFactor(Smash *lib, std::vector<Options> *options, Options *option) {
  uint8_t min_factor{0}, max_factor{0};
  bool set_value =
      lib->GetWorkFactorInformation(nullptr, &min_factor, &max_factor);
  do {
    if (set_value) option->SetWorkFactor(min_factor);
    SetShuffle(lib, options, option);
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
  double compression_time_;
  double decompression_time_;
  uint8_t option_;

  Result(const std::string &message, const uint64_t &uncompressed_size = 0,
         const uint64_t &compressed_size = 0,
         const double &compression_time = 0,
         const double &decompression_time = 0, const uint8_t &option = 0) {
    message_ = message;
    uncompressed_size_ = uncompressed_size;
    compressed_size_ = compressed_size;
    compression_time_ = compression_time;
    decompression_time_ = decompression_time;
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
        result = (static_cast<double>(other.uncompressed_size_) /
                  other.compression_time_) >
                 (static_cast<double>(uncompressed_size_) / compression_time_);
      }
    } else if (option_ == 3) {
      if (other.compressed_size_ < other.uncompressed_size_) {
        // Decompression Time
        result = (static_cast<double>(other.compressed_size_) /
                  other.decompression_time_) >
                 (static_cast<double>(compressed_size_) / decompression_time_);
      }
    } else if (option_ == 4) {
      if (other.compressed_size_ < other.uncompressed_size_) {
        // Total Time
        result = (static_cast<double>(other.uncompressed_size_) /
                  (other.compression_time_ + other.decompression_time_)) >
                 (static_cast<double>(uncompressed_size_) /
                  (compression_time_ + decompression_time_));
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
  bool all_options{false};
  int result{EXIT_FAILURE};
  if (GetParams(argc, argv, &opt, &input_file_name, &output_file_name,
                &compression_library_name, &all_options, &best_options,
                &best_result_number)) {
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
          lib->GetCompressedDataSize(uncompressed_data, uncompressed_size,
                                     &compressed_size);
          std::chrono::_V2::system_clock::time_point start, end;
          std::chrono::duration<double> compression_time, decompression_time;
          lib->SetOptionsCompressor(option);
          start = std::chrono::system_clock::now();
          lib->Compress(uncompressed_data, uncompressed_size, compressed_data,
                        &compressed_size);
          end = std::chrono::system_clock::now();
          compression_time = end - start;

          lib->SetOptionsDecompressor(option);
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
            if (CopyToFile(output_file_name, compressed_data,
                           compressed_size)) {
              std::string message = ShowResult(
                  lib, library_name, option, uncompressed_size, compressed_size,
                  compression_time.count(), decompression_time.count());
              results.push_back(
                  Result(message, uncompressed_size, compressed_size,
                         compression_time.count(), decompression_time.count(),
                         best_options));
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
      ShowTitle(uncompressed_size);
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
