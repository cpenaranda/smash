/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <string.h>

// SMASH LIBRARIES
#include <compression_libraries.hpp>
#include <smash_connection.hpp>
#include <smash_network.hpp>

bool SmashNetwork::Compress(std::shared_ptr<Smash> compressor,
                            std::shared_ptr<SmashMemory> memory) {
  uint64_t compressed_data_size = memory->GetSize();
  bool status = compressor->Compress(memory->GetCompressionLibraryData(),
                                     memory->GetCompressionLibraryDataSize(),
                                     memory->GetData(), &compressed_data_size);
  memory->SetCompressionLibraryDataSize(compressed_data_size);
  return status;
}

bool SmashNetwork::Decompress(std::shared_ptr<Smash> decompressor,
                              std::shared_ptr<SmashMemory> memory) {
  uint64_t decompressed_data_size{memory->GetDecompressionLibraryDataSize()};
  bool status = decompressor->Decompress(
      memory->GetData(), memory->GetCompressionLibraryDataSize(),
      memory->GetCompressionLibraryData(), &decompressed_data_size);
  return status;
}

void SmashNetwork::StreamBehaviour(std::shared_ptr<Smash> compressor,
                                   std::shared_ptr<Smash> decompressor,
                                   std::shared_ptr<SmashChunks> chunks_) {
  bool alive{true};
  bool status{true};
  std::shared_ptr<SmashMemory> memory;
  do {
    memory = chunks_->GetNextMemoryForCompressionLibrary();
    switch (memory->GetStatus()) {
      case SmashMemory::Status::Compressing:
        status = Compress(compressor, memory);
        chunks_->SetNextMemoryForCommunicationLayer(memory, status);
        break;
      case SmashMemory::Status::Decompressing:
        status = Decompress(decompressor, memory);
        chunks_->SetNextMemoryForCommunicationLayer(memory, status);
        break;
      case SmashMemory::Status::End:
        alive = false;
        break;
    }
  } while (alive);
}

bool SmashNetwork::Connect(const int &socket) {
  bool status{true};
  connection_.SetSocket(socket);
  uint32_t total_size = sizeof(options_compressor_) + sizeof(chunk_size_) +
                        sizeof(number_of_chunks_) + sizeof(threads_to_work_) +
                        library_name_compressor_.length();
  char *data = new char[total_size];
  uint32_t current_length{0};
  // Save compression options
  memcpy(data + current_length, &options_compressor_,
         sizeof(options_compressor_));
  current_length += sizeof(options_compressor_);
  // Save size of chunks
  memcpy(data + current_length, &chunk_size_, sizeof(chunk_size_));
  current_length += sizeof(chunk_size_);
  // Save number of chunks
  memcpy(data + current_length, &number_of_chunks_, sizeof(number_of_chunks_));
  current_length += sizeof(number_of_chunks_);
  // Save number of threads
  memcpy(data + current_length, &threads_to_work_, sizeof(threads_to_work_));
  current_length += sizeof(threads_to_work_);
  // Save compression library name
  memcpy(data + current_length, library_name_compressor_.data(),
         library_name_compressor_.length());
  current_length += library_name_compressor_.length();

  // Send compression information
  if (status = (connection_.Write(data, total_size) > 0)) {
    // Recv decompression information
    if (status = (connection_.Read(data, &total_size) > 0)) {
      current_length = 0;
      // Get decompression options
      memcpy(&options_decompressor_, data + current_length,
             sizeof(options_decompressor_));
      current_length += sizeof(options_decompressor_);
      // Get size of chunks
      uint32_t chunk_size{0};
      memcpy(&chunk_size, data + current_length, sizeof(chunk_size));
      current_length += sizeof(chunk_size);
      if (status =
              ((chunk_size_ && !chunk_size) || (!chunk_size_ && chunk_size))) {
        chunk_size_ = chunk_size_ ? chunk_size_ : chunk_size;
        // Get number of chunks
        uint16_t number_of_chunks{0};
        memcpy(&number_of_chunks, data + current_length,
               sizeof(number_of_chunks));
        current_length += sizeof(number_of_chunks);
        if (status = ((number_of_chunks_ && !number_of_chunks) ||
                      (!number_of_chunks_ && number_of_chunks))) {
          number_of_chunks_ =
              number_of_chunks_ ? number_of_chunks_ : number_of_chunks;
          // Get number of threads
          uint8_t threads_to_work{0};
          memcpy(&threads_to_work, data + current_length,
                 sizeof(threads_to_work));
          current_length += sizeof(threads_to_work);
          if (status = ((threads_to_work_ && !threads_to_work) ||
                        (!threads_to_work_ && threads_to_work))) {
            threads_to_work_ =
                threads_to_work_ ? threads_to_work_ : threads_to_work;
            // Get decompression library name
            library_name_decompressor_ =
                std::string(data + current_length, data + total_size);
            Initilize();
            // Check they are at the same point
            connection_.Write(reinterpret_cast<char *>(&status),
                              sizeof(status));
            connection_.Read(reinterpret_cast<char *>(&status), nullptr);
          }
        }
      }
    }
  }
  return status;
}

// Write_v1 works in the following way:
// 1- Set a piece of data to compress
// 2- Waits until the piece of data has been compressed
// 3- Sends the compressed piece of data
// 4- Starts again if there are more data
int SmashNetwork::Write_v1(void *buffer, const uint32_t &number_bytes,
                           uint64_t *compressed_size, const bool &ack) {
  uint32_t total_write{0};
  *compressed_size = 0;
  std::shared_ptr<SmashMemory> memory;
  int res{0}, current_res{0};
  for (uint32_t current_position = 0;
       current_position < number_bytes && current_res >= 0;
       current_position += total_write) {
    total_write = ((number_bytes - current_position) > chunk_size_)
                      ? chunk_size_
                      : (number_bytes - current_position);
    // 1- Set a piece of data to compress
    chunks_->SetNextMemoryForCompressionLibrary(
        reinterpret_cast<char *>(buffer) + current_position, total_write);
    // 2- Waits until the piece of data has been compressed
    memory = chunks_->GetNextMemoryForCommunicationLayer();
    *compressed_size += memory->GetCompressionLibraryDataSize();
    // 3- Sends the compressed piece of data
    res += current_res = connection_.Write(
        memory->GetData(), memory->GetCompressionLibraryDataSize(),
        ack && total_write != chunk_size_);
    // 4- Starts again if there are more data
  }
  if (current_res < 0) res = -1;
  return res;
}

// Read_v1 works in the following way:
// 1- Gets the memory where a compressed piece of data must be stored
// 2- Waits until the compressed piece of data has been received
// 3- Set the compressed piece of data to decompress
// 4- Starts again if there are more data
int SmashNetwork::Read_v1(void *buffer, const uint32_t &number_bytes,
                          const bool &ack) {
  uint32_t total_read{0};
  uint32_t compressed_size{0};
  std::shared_ptr<SmashMemory> memory;
  int res{0}, current_res{0};
  for (uint32_t current_position = 0;
       current_position < number_bytes && current_res >= 0;
       current_position += total_read) {
    total_read = ((number_bytes - current_position) > chunk_size_)
                     ? chunk_size_
                     : (number_bytes - current_position);
    // 1- Gets the memory where a compressed piece of data must be stored
    memory = chunks_->GetNextMemoryForCommunicationLayer();
    // 2- Waits until the compressed piece of data has been received
    res += current_res = connection_.Read(memory->GetData(), &compressed_size,
                                          ack && total_read != chunk_size_);
    memory->SetDecompressionLibraryDataSize(total_read);
    // 3- Set the compressed piece of data to decompress
    chunks_->SetNextMemoryForCompressionLibrary(
        memory, reinterpret_cast<char *>(buffer) + current_position,
        compressed_size);
    // 4- Starts again if there are more data
  }
  if (!chunks_->Synchronize()) {
    res = -1;
  } else if (current_res < 0) {
    res = -1;
  }
  return res;
}

bool SmashNetwork::Initilize() {
  bool status{true};
  uint64_t compress_data_size{0}, decompress_data_size{0};
  Smash(library_name_compressor_)
      .GetCompressedDataSize(nullptr, chunk_size_, &compress_data_size);
  Smash(library_name_decompressor_)
      .GetCompressedDataSize(nullptr, chunk_size_, &decompress_data_size);
  threads_.reserve(threads_to_work_);
  compressors_.reserve(threads_to_work_ + 1);
  decompressors_.reserve(threads_to_work_ + 1);
  chunks_ = std::make_shared<SmashChunks>(
      number_of_chunks_, compress_data_size > decompress_data_size
                             ? compress_data_size
                             : decompress_data_size);
  for (uint16_t iThread = 0; iThread < threads_to_work_ + 1; ++iThread) {
    compressors_.push_back(std::make_shared<Smash>(library_name_compressor_));
    decompressors_.push_back(
        std::make_shared<Smash>(library_name_decompressor_));
    if (status =
            compressors_[iThread]->SetOptionsCompressor(&options_compressor_)) {
      if (status = decompressors_[iThread]->SetOptionsDecompressor(
              &options_decompressor_)) {
        if (iThread < threads_to_work_) {
          threads_.push_back(std::thread(StreamBehaviour, compressors_[iThread],
                                         decompressors_[iThread], chunks_));
        }
      }
    }
  }
  return status;
}

void SmashNetwork::RemoveStreams() {
  chunks_->TheEnd();
  for (uint16_t iThread = 0; iThread < threads_to_work_; ++iThread) {
    threads_[iThread].join();
  }
}

SmashNetwork::SmashNetwork(const std::string &compression_library_name,
                           const Options &options,
                           const uint8_t &threads_to_work,
                           const uint32_t &chunk_size,
                           const uint16_t &number_of_chunks)
    : library_name_compressor_(compression_library_name),
      options_compressor_(options),
      threads_to_work_(threads_to_work),
      chunk_size_(chunk_size),
      number_of_chunks_(number_of_chunks) {}

SmashNetwork::~SmashNetwork() {
  RemoveStreams();
  compressors_.clear();
  decompressors_.clear();
}
