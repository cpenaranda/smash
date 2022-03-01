/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>

// SMASH LIBRARIES
#include <compression_libraries.hpp>
#include <smash.hpp>
class Utils {
 private:
  inline static const std::string how_to_run_ = "To run the smash benchmark:";
  inline static const std::string how_to_execute_ =
      " -c <library_name> -i <name_file>";
  inline static const std::string available_arguments_ = "Available arguments:";

  inline static const std::string help_p1_ = "-h";
  inline static const std::string help_p2_ = "--help";
  inline static const std::string available_p1_ = "-a";
  inline static const std::string available_p2_ = "--available_libraries";
  inline static const std::string compression_p1_ = "-c";
  inline static const std::string compression_p2_ = "--compression_library";
  inline static const std::string input_p1_ = "-i";
  inline static const std::string input_p2_ = "--input_file";
  inline static const std::string output_p1_ = "-o";
  inline static const std::string output_p2_ = "--output_file";
  inline static const std::string effort_p1_ = "-e";
  inline static const std::string effort_p2_ = "--best_effort";
  inline static const std::string repetitions_p1_ = "-n";
  inline static const std::string repetitions_p2_ = "--repetition_number";
  inline static const std::string best_p1_ = "-b";
  inline static const std::string best_p2_ = "--best";
  inline static const std::string level_p1_ = "-l";
  inline static const std::string level_p2_ = "--level";
  inline static const std::string window_p1_ = "-s";
  inline static const std::string window_p2_ = "--window_size";
  inline static const std::string mode_p1_ = "-m";
  inline static const std::string mode_p2_ = "--mode";
  inline static const std::string work_p1_ = "-w";
  inline static const std::string work_p2_ = "--work_factor";
  inline static const std::string flags_p1_ = "-f";
  inline static const std::string flags_p2_ = "--flags";
  inline static const std::string reference_p1_ = "-r";
  inline static const std::string reference_p2_ = "--back_reference_bits";
  inline static const std::string threads_p1_ = "-t";
  inline static const std::string threads_p2_ = "--threads";

  static const uint16_t length_left_message_ = 45;
  inline static const std::string help_left_message_ =
      help_p1_ + ", " + help_p2_;
  inline static const std::string help_library_left_message_ =
      help_p1_ + ", " + help_p2_ + " <library>";
  inline static const std::string available_libraries_left_message_ =
      available_p1_ + ", " + available_p2_;
  inline static const std::string compression_library_left_message_ =
      compression_p1_ + ", " + compression_p2_ + " <library_name>";
  inline static const std::string input_file_left_message_ =
      input_p1_ + ", " + input_p2_ + " <file_name>";
  inline static const std::string output_file_left_message_ =
      output_p1_ + ", " + output_p2_ + " <file_name>";
  inline static const std::string best_effort_left_message_ =
      effort_p1_ + ", " + effort_p2_;
  inline static const std::string repetition_number_left_message_ =
      repetitions_p1_ + ", " + repetitions_p2_ + " <number>";
  inline static const std::string best_left_message_ =
      best_p1_ + ", " + best_p2_ + " <option> <number>";
  inline static const std::string level_left_message_ =
      level_p1_ + ", " + level_p2_ + " <number>";
  inline static const std::string window_size_left_message_ =
      window_p1_ + ", " + window_p2_ + " <number>";
  inline static const std::string mode_left_message_ =
      mode_p1_ + ", " + mode_p2_ + " <number>";
  inline static const std::string work_factor_left_message_ =
      work_p1_ + ", " + work_p2_ + " <number>";
  inline static const std::string flags_left_message_ =
      flags_p1_ + ", " + flags_p2_ + " <number>";
  inline static const std::string back_reference_bits_left_message_ =
      reference_p1_ + ", " + reference_p2_ + " <number>";
  inline static const std::string threads_left_message_ =
      threads_p1_ + ", " + threads_p2_ + " <number>";

  static const uint16_t length_right_message_ = 71;
  inline static const std::string help_right_message_ = "Show this message";
  inline static const std::string help_library_right_message_ =
      "Show information about a specific library";
  inline static const std::string available_libraries_right_message_ =
      "Show a list of the available libraries";
  inline static const std::string compression_library_right_message_ =
      "Library name to use in compression/decompression";
  inline static const std::string input_file_right_message_ =
      "File name to compress";
  inline static const std::string output_file_right_message_ =
      "File name where the compress data is stored";
  inline static const std::string best_effort_right_message_ =
      "Run all possible configurations of the selected library";
  inline static const std::string repetition_number_right_message_ =
      "Compression and decompression are done <number> times (1 by default)";
  inline static const std::string best_right_message_ =
      "Get the <number> configurations of the selected library                "
      "with the best <option>. Available options:                             "
      "1: Compression time                                                    "
      "2: Decompression time                                                  "
      "3: Total time";
  inline static const std::string level_right_message_ =
      "Compression level to use (1 by default)";
  inline static const std::string window_size_right_message_ =
      "Set window size (15 by default)";
  inline static const std::string mode_right_message_ =
      "Specifies the mode used (0 by default)";
  inline static const std::string work_factor_right_message_ =
      "Controls how the compression works with repetitive data (30 by default)";
  inline static const std::string flags_right_message_ =
      "Flags to use (0 by default)";
  inline static const std::string back_reference_bits_right_message_ =
      "Number of bits used for back-reference (4 by default)";
  inline static const std::string threads_right_message_ =
      "Threads used in algorithms (1 by default)";
  inline static const std::string values_depend_libraries_message_ =
      "Values depend of different libraries";

  static const uint16_t size_row_library_ = 13;
  static const uint16_t size_row_level_ = 8;
  static const uint16_t size_row_window_ = 9;
  static const uint16_t size_row_mode_ = 17;
  static const uint16_t size_row_factor_ = 6;
  static const uint16_t size_row_flags_ = 16;
  static const uint16_t size_row_threads_ = 10;
  static const uint16_t size_row_back_reference_ = 6;
  static const uint16_t size_rows_original_data_ = 16;
  static const uint16_t size_rows_packed_data_ = 14;
  static const uint16_t size_rows_ratio_ = 9;
  static const uint16_t size_rows_compress_ = 14;
  static const uint16_t size_rows_decompress_ = 14;
  static const uint16_t size_rows_total_ = 14;

  static void PrintDescription(std::string description);

  static void PrintLine(const std::string &left_message,
                        std::string right_message,
                        const std::vector<std::string> &descriptions);

  static void PrintLine(const std::string &left_message,
                        std::string right_message,
                        const std::string &aditional_right_message = "");

  static bool Check(const char *const param, const std::string &first_value,
                    const std::string &second_value);

  static void ListCompressionLibraries();

  static std::string ToStringDouble(const double &value);

  static void SetBackReferenceBits(Smash *lib, std::vector<Options> *options,
                                   Options *option);

  static void SetNumberThreads(Smash *lib, std::vector<Options> *options,
                               Options *option);

  static void SetFlags(Smash *lib, std::vector<Options> *options,
                       Options *option);

  static void SetWorkFactor(Smash *lib, std::vector<Options> *options,
                            Options *option);

  static void SetWindowSize(Smash *lib, std::vector<Options> *options,
                            Options *option);

  static void SetMode(Smash *lib, std::vector<Options> *options,
                      Options *option, const uint8_t &level);

  static void SetCopressionLevel(Smash *lib, std::vector<Options> *options);

 public:
  static void ShowMessage(const std::string &exe);

  static void ShowLibraryInformation(const std::string &library_name,
                                     const std::string &exe);

  static bool GetParams(const int &number_params, const char *const params[],
                        Options *opt, std::string *input_file_name,
                        std::string *output_file_name,
                        std::string *compression_library_name,
                        bool *all_options, uint8_t *option,
                        uint32_t *result_number, uint32_t *repetitions);

  static void ShowTitle(const uint64_t &size, const uint64_t &repetitions);

  static std::string ShowResult(Smash *lib, const std::string &library_name,
                                Options opt, const uint64_t &uncompressed_size,
                                const uint64_t &compressed_size,
                                const double &mean_vel_compression,
                                const double &error_vel_compression,
                                const double &mean_vel_decompression,
                                const double &error_vel_decompression,
                                const double &mean_vel_total,
                                const double &error_vel_total);

  static void GetAllOptions(Smash *lib, std::vector<Options> *options);
};
