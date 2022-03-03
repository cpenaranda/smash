/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <iomanip>
#include <string>

// SMASH LIBRARIES
#include <compression_libraries.hpp>
#include <smash.hpp>
#include <utils.hpp>

void Utils::PrintDescription(std::string description) {
  while (length_right_message_ < description.size()) {
    std::cout << std::left << std::setw(length_left_message_)
              << std::setfill(' ') << " ";
    std::cout << std::left << std::setw(length_right_message_)
              << std::setfill(' ')
              << description.substr(0, length_right_message_);
    std::cout << std::endl;
    description = description.substr(length_right_message_);
  }
  std::cout << std::left << std::setw(length_left_message_) << std::setfill(' ')
            << " ";
  std::cout << std::left << std::setw(length_right_message_)
            << std::setfill(' ')
            << description.substr(0, length_right_message_);
  std::cout << std::endl;
}

void Utils::PrintLine(const std::string &left_message,
                      std::string right_message,
                      const std::vector<std::string> &descriptions) {
  std::cout << std::left << std::setw(length_left_message_) << std::setfill(' ')
            << " " + left_message;
  std::cout << std::left << std::setw(length_right_message_)
            << std::setfill(' ')
            << right_message.substr(0, length_right_message_);
  std::cout << std::endl;
  if (length_right_message_ < right_message.size()) {
    right_message = right_message.substr(length_right_message_);
    PrintDescription(right_message);
  }
  for (auto &description : descriptions) {
    PrintDescription(description);
  }
  std::cout << std::endl;
}

void Utils::PrintLine(const std::string &left_message,
                      std::string right_message,
                      const std::string &aditional_right_message) {
  std::cout << std::left << std::setw(length_left_message_) << std::setfill(' ')
            << " " + left_message;
  std::cout << std::left << std::setw(length_right_message_)
            << std::setfill(' ')
            << right_message.substr(0, length_right_message_);
  std::cout << std::endl;
  if (length_right_message_ < right_message.size()) {
    right_message = right_message.substr(length_right_message_);
    PrintDescription(right_message);
  }
  if (!aditional_right_message.empty()) {
    PrintDescription(aditional_right_message);
  }
  std::cout << std::endl;
}

bool Utils::Check(const char *const param, const std::string &first_value,
                  const std::string &second_value) {
  return (first_value.compare(param) == 0) | (second_value.compare(param) == 0);
}

void Utils::ListCompressionLibraries() {
  std::cout << "Available compression libraries:" << std::endl << std::endl;
  std::cout << std::left << std::setw(15) << std::setfill(' ') << "all"
            << "- "
            << "Run all the compression libraries with specific options"
            << std::endl;
  CompressionLibraries().GetListInformation();
}

std::string Utils::ToStringDouble(const double &value) {
  std::ostringstream out;
  out.precision(2);
  out << std::fixed << value;
  return out.str();
}

void Utils::SetBackReferenceBits(Smash *lib, std::vector<Options> *options,
                                 Options *option) {
  uint16_t min_bits{0}, max_bits{0};
  bool set_value = lib->GetBackReferenceBitsInformation(
      nullptr, reinterpret_cast<uint8_t *>(&min_bits),
      reinterpret_cast<uint8_t *>(&max_bits));
  do {
    if (set_value) option->SetBackReferenceBits(min_bits);
    options->push_back(*option);
    min_bits += 51;
  } while (min_bits <= max_bits);
}

void Utils::SetNumberThreads(Smash *lib, std::vector<Options> *options,
                             Options *option) {
  uint16_t min_threads{0}, max_threads{0};
  bool set_value = lib->GetNumberThreadsInformation(
      nullptr, reinterpret_cast<uint8_t *>(&min_threads),
      reinterpret_cast<uint8_t *>(&max_threads));
  do {
    if (set_value) option->SetNumberThreads(min_threads);
    SetBackReferenceBits(lib, options, option);
    min_threads += 2;
  } while (min_threads <= max_threads);
}

void Utils::SetFlags(Smash *lib, std::vector<Options> *options,
                     Options *option) {
  uint16_t min_flag{0}, max_flag{0};
  bool set_value =
      lib->GetFlagsInformation(nullptr, reinterpret_cast<uint8_t *>(&min_flag),
                               reinterpret_cast<uint8_t *>(&max_flag));
  do {
    if (set_value) option->SetFlags(min_flag);
    SetNumberThreads(lib, options, option);
    ++min_flag;
  } while (min_flag <= max_flag);
}

void Utils::SetWorkFactor(Smash *lib, std::vector<Options> *options,
                          Options *option) {
  uint16_t min_factor{0}, max_factor{0};
  bool set_value = lib->GetWorkFactorInformation(
      nullptr, reinterpret_cast<uint8_t *>(&min_factor),
      reinterpret_cast<uint8_t *>(&max_factor));
  do {
    if (set_value) option->SetWorkFactor(min_factor);
    SetFlags(lib, options, option);
    min_factor += 5;
  } while (min_factor <= max_factor);
}

void Utils::SetWindowSize(Smash *lib, std::vector<Options> *options,
                          Options *option) {
  uint64_t min_window{0}, max_window{0};
  bool set_value = lib->GetWindowSizeInformation(
      nullptr, reinterpret_cast<uint32_t *>(&min_window),
      reinterpret_cast<uint32_t *>(&max_window));
  do {
    if (set_value) option->SetWindowSize(min_window);
    SetWorkFactor(lib, options, option);
    min_window += 5;
  } while (min_window <= max_window);
}

void Utils::SetMode(Smash *lib, std::vector<Options> *options, Options *option,
                    const uint8_t &level) {
  uint16_t min_mode{0}, max_mode{0};
  bool set_value =
      lib->GetModeInformation(nullptr, reinterpret_cast<uint8_t *>(&min_mode),
                              reinterpret_cast<uint8_t *>(&max_mode), level);
  do {
    if (set_value) option->SetMode(min_mode);
    SetWindowSize(lib, options, option);
    ++min_mode;
  } while (min_mode <= max_mode);
}

void Utils::SetCopressionLevel(Smash *lib, std::vector<Options> *options) {
  Options option;
  uint16_t min_level{0}, max_level{0};
  bool set_value = lib->GetCompressionLevelInformation(
      nullptr, reinterpret_cast<uint8_t *>(&min_level),
      reinterpret_cast<uint8_t *>(&max_level));
  do {
    if (set_value) option.SetCompressionLevel(min_level);
    SetMode(lib, options, &option, min_level);
    ++min_level;
  } while (min_level <= max_level);
}

void Utils::ShowMessage(const std::string &exe) {
  std::cout << how_to_run_ << std::endl;
  std::cout << " " << exe << how_to_execute_ << std::endl << std::endl;
  std::cout << available_arguments_ << std::endl << std::endl;
  PrintLine(help_left_message_, help_right_message_);
  PrintLine(help_library_left_message_, help_library_right_message_);
  PrintLine(available_libraries_left_message_,
            available_libraries_right_message_);
  PrintLine(compression_library_left_message_,
            compression_library_right_message_);
  PrintLine(input_file_left_message_, input_file_right_message_);
  PrintLine(output_file_left_message_, output_file_right_message_);
  PrintLine(best_effort_left_message_, best_effort_right_message_);
  PrintLine(repetition_number_left_message_, repetition_number_right_message_);
  PrintLine(best_left_message_, best_right_message_);
  PrintLine(level_left_message_, level_right_message_,
            values_depend_libraries_message_);
  PrintLine(window_size_left_message_, window_size_right_message_,
            values_depend_libraries_message_);
  PrintLine(mode_left_message_, mode_right_message_,
            values_depend_libraries_message_);
  PrintLine(work_factor_left_message_, work_factor_right_message_,
            values_depend_libraries_message_);
  PrintLine(flags_left_message_, flags_right_message_,
            values_depend_libraries_message_);
  PrintLine(back_reference_bits_left_message_,
            back_reference_bits_right_message_,
            values_depend_libraries_message_);
  PrintLine(threads_left_message_, threads_right_message_,
            values_depend_libraries_message_);
}

void Utils::ShowLibraryInformation(const std::string &library_name,
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
    std::cout << how_to_run_ << std::endl << std::endl;
    PrintLine(input_file_left_message_, input_file_right_message_);
    PrintLine(output_file_left_message_, output_file_right_message_);
    PrintLine(repetition_number_left_message_,
              repetition_number_right_message_);

    std::vector<std::string> information;
    lib.GetCompressionLevelInformation(&information);
    if (!information.empty()) {
      PrintLine(level_left_message_, level_right_message_, information);
    }
    lib.GetWindowSizeInformation(&information);
    if (!information.empty()) {
      PrintLine(window_size_left_message_, window_size_right_message_,
                information);
    }
    lib.GetModeInformation(&information);
    if (!information.empty()) {
      PrintLine(mode_left_message_, mode_right_message_, information);
    }
    lib.GetWorkFactorInformation(&information);
    if (!information.empty()) {
      PrintLine(work_factor_left_message_, work_factor_right_message_,
                information);
    }
    lib.GetFlagsInformation(&information);
    if (!information.empty()) {
      PrintLine(flags_left_message_, flags_right_message_, information);
    }
    lib.GetBackReferenceBitsInformation(&information);
    if (!information.empty()) {
      PrintLine(back_reference_bits_left_message_,
                back_reference_bits_right_message_, information);
    }
    lib.GetNumberThreadsInformation(&information);
    if (!information.empty()) {
      PrintLine(threads_left_message_, threads_right_message_, information);
    }
  }
}

bool Utils::GetParams(const int &number_params, const char *const params[],
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
    if (Check(params[n], help_p1_, help_p2_)) {
      if (n + 1 < number_params &&
          std::string(params[n + 1]).find("-") == std::string::npos) {
        ShowLibraryInformation(params[n + 1], params[0]);
      } else {
        ShowMessage(params[0]);
      }
      exit(EXIT_SUCCESS);
    } else if (Check(params[n], available_p1_, available_p2_)) {
      ListCompressionLibraries();
      exit(EXIT_SUCCESS);
    } else if (Check(params[n], compression_p1_, compression_p2_)) {
      ++n;
      if (n < number_params && compression_library_name->empty()) {
        *compression_library_name = params[n];
      } else {
        error = end = true;
      }
    } else if (Check(params[n], input_p1_, input_p2_)) {
      ++n;
      if (n < number_params && input_file_name->empty()) {
        *input_file_name = params[n];
      } else {
        error = end = true;
      }
    } else if (Check(params[n], output_p1_, output_p2_)) {
      ++n;
      if (n < number_params && output_file_name->empty()) {
        *output_file_name = params[n];
      } else {
        error = end = true;
      }
    } else if (Check(params[n], level_p1_, level_p2_)) {
      ++n;
      if (n < number_params && !compression_level_set) {
        opt->SetCompressionLevel(atoi(params[n]));
        compression_level_set = true;
      } else {
        error = end = true;
      }
    } else if (Check(params[n], window_p1_, window_p2_)) {
      ++n;
      if (n < number_params && !window_size_set) {
        opt->SetWindowSize(atoi(params[n]));
        window_size_set = true;
      } else {
        error = end = true;
      }
    } else if (Check(params[n], mode_p1_, mode_p2_)) {
      ++n;
      if (n < number_params && !mode_set) {
        opt->SetMode(atoi(params[n]));
        mode_set = true;
      } else {
        error = end = true;
      }
    } else if (Check(params[n], work_p1_, work_p2_)) {
      ++n;
      if (n < number_params && !work_factor_set) {
        opt->SetWorkFactor(atoi(params[n]));
        work_factor_set = true;
      } else {
        error = end = true;
      }
    } else if (Check(params[n], flags_p1_, flags_p2_)) {
      ++n;
      if (n < number_params && !flags_set) {
        opt->SetFlags(atoi(params[n]));
        flags_set = true;
      } else {
        error = end = true;
      }
    } else if (Check(params[n], reference_p1_, reference_p2_)) {
      ++n;
      if (n < number_params && !back_reference_bits_set) {
        opt->SetBackReferenceBits(atoi(params[n]));
        back_reference_bits_set = true;
      } else {
        error = end = true;
      }
    } else if (Check(params[n], threads_p1_, threads_p2_)) {
      ++n;
      if (n < number_params && !threads_set) {
        opt->SetNumberThreads(atoi(params[n]));
        threads_set = true;
      } else {
        error = end = true;
      }
    } else if (Check(params[n], effort_p1_, effort_p2_)) {
      if (!best_effort_set) {
        best_effort_set = true;
        *all_options = true;
      } else {
        error = end = true;
      }
    } else if (Check(params[n], best_p1_, best_p2_)) {
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
    } else if (Check(params[n], repetitions_p1_, repetitions_p2_)) {
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

void Utils::ShowTitle(const uint64_t &size, const uint64_t &repetitions) {
  const uint16_t size_rows_original_data =
      (size_rows_original_data_ < (std::to_string(size).size() + 9))
          ? std::to_string(size).size() + 9
          : size_rows_original_data_;

  const uint16_t size_rows_packed_data =
      (size_rows_packed_data_ < size_rows_original_data)
          ? size_rows_original_data
          : size_rows_packed_data_;

  std::cout << std::left << std::setw(size_row_library_) << std::setfill(' ')
            << "| Library";
  std::cout << std::left << std::setw(size_row_level_) << std::setfill(' ')
            << "| Level";
  std::cout << std::left << std::setw(size_row_window_) << std::setfill(' ')
            << "| Window";
  std::cout << std::left << std::setw(size_row_mode_) << std::setfill(' ')
            << "| Mode";
  std::cout << std::left << std::setw(size_row_factor_) << std::setfill(' ')
            << "| WF";
  std::cout << std::left << std::setw(size_row_flags_) << std::setfill(' ')
            << "| Flags";
  std::cout << std::left << std::setw(size_row_threads_) << std::setfill(' ')
            << "| Threads";
  std::cout << std::left << std::setw(size_row_back_reference_)
            << std::setfill(' ') << "| BR";
  std::cout << std::left << std::setw(size_rows_original_data)
            << std::setfill(' ') << "| Original data";
  std::cout << std::left << std::setw(size_rows_packed_data)
            << std::setfill(' ') << "| Packed data";
  std::cout << std::left << std::setw(size_rows_ratio_) << std::setfill(' ')
            << "| Ratio";
  std::cout << std::left << std::setw(size_rows_compress_) << std::setfill(' ')
            << "| Compress";
  if (repetitions > 1) {
    std::cout << std::left << std::setw(size_rows_compress_ + 3)
              << std::setfill(' ') << "| Error Compress";
  }
  std::cout << std::left << std::setw(size_rows_decompress_)
            << std::setfill(' ') << "| Decompress";
  if (repetitions > 1) {
    std::cout << std::left << std::setw(size_rows_compress_ + 5)
              << std::setfill(' ') << "| Error Decompress";
  }
  std::cout << std::left << std::setw(size_rows_total_) << std::setfill(' ')
            << "| Total";
  if (repetitions > 1) {
    std::cout << std::left << std::setw(size_rows_compress_)
              << std::setfill(' ') << "| Error Total";
  }
  std::cout << "|" << std::endl;

  std::cout << std::left
            << std::setw(size_row_library_ + size_row_level_ +
                         size_row_window_ + size_row_mode_ + size_row_factor_ +
                         size_row_flags_ + size_row_threads_ +
                         size_row_back_reference_ + size_rows_original_data +
                         size_rows_packed_data + size_rows_ratio_ +
                         size_rows_compress_ + size_rows_decompress_ +
                         size_rows_total_ + 1 +
                         ((repetitions > 1)
                              ? size_rows_compress_ + size_rows_decompress_ +
                                    size_rows_total_ + 3 + 5
                              : 0))
            << std::setfill('-') << "-" << std::endl;
}

std::string Utils::ShowResult(
    Smash *lib, const std::string &library_name, Options opt,
    const uint64_t &uncompressed_size, const uint64_t &compressed_size,
    const double &mean_vel_compression, const double &error_vel_compression,
    const double &mean_vel_decompression, const double &error_vel_decompression,
    const double &mean_vel_total, const double &error_vel_total) {
  const uint16_t size_rows_original_data =
      (size_rows_original_data_ <
       (std::to_string(uncompressed_size).size() + 9))
          ? std::to_string(uncompressed_size).size() + 9
          : size_rows_original_data_;

  const uint16_t size_rows_packed_data =
      (size_rows_packed_data_ < size_rows_original_data)
          ? size_rows_original_data
          : size_rows_packed_data_;

  std::ostringstream result;
  bool repetitions = error_vel_compression;
  result << std::left << std::setw(size_row_library_) << std::setfill(' ')
         << "| " + library_name;

  if (lib->GetCompressionLevelInformation()) {
    result << std::left << std::setw(size_row_level_) << std::setfill(' ')
           << "| " + std::to_string(opt.GetCompressionLevel());
  } else {
    result << std::left << std::setw(size_row_level_ - 1) << std::setfill('-')
           << "| "
           << " ";
  }

  if (lib->GetWindowSizeInformation()) {
    result << std::left << std::setw(size_row_window_) << std::setfill(' ')
           << "| " + std::to_string(opt.GetWindowSize());
  } else {
    result << std::left << std::setw(size_row_window_ - 1) << std::setfill('-')
           << "| "
           << " ";
  }

  if (lib->GetModeInformation()) {
    result << std::left << std::setw(size_row_mode_) << std::setfill(' ')
           << "| " + lib->GetModeName(opt.GetMode());
  } else {
    result << std::left << std::setw(size_row_mode_ - 1) << std::setfill('-')
           << "| "
           << " ";
  }

  if (lib->GetWorkFactorInformation()) {
    result << std::left << std::setw(size_row_factor_) << std::setfill(' ')
           << "| " + std::to_string(opt.GetWorkFactor());
  } else {
    result << std::left << std::setw(size_row_factor_ - 1) << std::setfill('-')
           << "| "
           << " ";
  }

  if (lib->GetFlagsInformation()) {
    result << std::left << std::setw(size_row_flags_) << std::setfill(' ')
           << "| " + lib->GetFlagsName(opt.GetFlags());
  } else {
    result << std::left << std::setw(size_row_flags_ - 1) << std::setfill('-')
           << "| "
           << " ";
  }

  if (lib->GetNumberThreadsInformation()) {
    result << std::left << std::setw(size_row_threads_) << std::setfill(' ')
           << "| " + std::to_string(opt.GetNumberThreads());
  } else {
    result << std::left << std::setw(size_row_threads_ - 1) << std::setfill('-')
           << "| "
           << " ";
  }

  if (lib->GetBackReferenceBitsInformation()) {
    result << std::left << std::setw(size_row_back_reference_)
           << std::setfill(' ')
           << "| " + std::to_string(opt.GetBackReferenceBits());
  } else {
    result << std::left << std::setw(size_row_back_reference_ - 1)
           << std::setfill('-') << "| "
           << " ";
  }

  result << std::left << std::setw(size_rows_original_data) << std::setfill(' ')
         << "| " + std::to_string(uncompressed_size) + " Bytes";

  result << std::left << std::setw(size_rows_packed_data) << std::setfill(' ')
         << "| " + std::to_string(compressed_size) + " Bytes";
  result << std::left << std::setw(size_rows_ratio_) << std::setfill(' ')
         << "| " + ToStringDouble((static_cast<double>(uncompressed_size) /
                                   static_cast<double>(compressed_size)));

  result << std::left << std::setw(size_rows_compress_) << std::setfill(' ')
         << "| " + ToStringDouble(mean_vel_compression) + " MB/s";
  if (repetitions) {
    result << std::left << std::setw(size_rows_compress_ + 3)
           << std::setfill(' ')
           << "| " + ToStringDouble(error_vel_compression) + " MB/s";
  }
  result << std::left << std::setw(size_rows_decompress_) << std::setfill(' ')
         << "| " + ToStringDouble(mean_vel_decompression) + " MB/s";
  if (repetitions) {
    result << std::left << std::setw(size_rows_decompress_ + 5)
           << std::setfill(' ')
           << "| " + ToStringDouble(error_vel_decompression) + " MB/s";
  }
  result << std::left << std::setw(size_rows_total_) << std::setfill(' ')
         << "| " + ToStringDouble(mean_vel_total) + " MB/s";
  if (repetitions) {
    result << std::left << std::setw(size_rows_total_) << std::setfill(' ')
           << "| " + ToStringDouble(error_vel_total) + " MB/s";
  }

  result << "|" << std::endl;
  return result.str();
}

void Utils::GetAllOptions(Smash *lib, std::vector<Options> *options) {
  options->clear();
  SetCopressionLevel(lib, options);
}