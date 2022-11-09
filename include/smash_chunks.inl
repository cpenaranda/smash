/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

inline std::shared_ptr<SmashMemory>
SmashChunks::GetNextMemoryForCompressionLibrary() {
  std::unique_lock<std::mutex> lock(mutex_for_compression_library_);
  condition_for_compression_library_.wait(lock, [this] {
    return (chunks_[first_available_for_compression_library_]->GetStatus() ==
            SmashMemory::Status::ReadyForCompression) ||
           (chunks_[first_available_for_compression_library_]->GetStatus() ==
            SmashMemory::Status::ReadyForDecompression) ||
           (chunks_[first_available_for_compression_library_]->GetStatus() ==
            SmashMemory::Status::End);
  });
  std::shared_ptr<SmashMemory> shrd =
      chunks_[first_available_for_compression_library_];
  switch (shrd->GetStatus()) {
    case SmashMemory::Status::ReadyForCompression:
      shrd->SetStatus(SmashMemory::Status::Compressing);
      break;
    case SmashMemory::Status::ReadyForDecompression:
      shrd->SetStatus(SmashMemory::Status::Decompressing);
      break;
  }
  first_available_for_compression_library_ =
      (++first_available_for_compression_library_) % number_of_chunks_;
  condition_for_compression_library_.notify_one();
  return shrd;
}

inline std::shared_ptr<SmashMemory>
SmashChunks::GetNextMemoryForCommunicationLayer() {
  // Just one thread
  {
    std::unique_lock<std::mutex> lock(mutex_for_communication_layer_);
    condition_for_communication_layer_.wait(lock, [this] {
      return (chunks_[first_available_for_communication_layer_]->GetStatus() ==
              SmashMemory::Status::Transferring) ||
             (chunks_[first_available_for_communication_layer_]->GetStatus() ==
              SmashMemory::Status::ReadyForCommunicationLayer) ||
             (chunks_[first_available_for_communication_layer_]->GetStatus() ==
              SmashMemory::Status::Error);
    });
  }
  std::shared_ptr<SmashMemory> shrd =
      chunks_[first_available_for_communication_layer_];
  if (shrd->GetStatus() != SmashMemory::Status::Error) {
    shrd->SetStatus(SmashMemory::Status::Transferring);
    first_available_for_communication_layer_ =
        (++first_available_for_communication_layer_) % number_of_chunks_;
    // Just one thread
    // condition_for_communication_layer_.notify_one();
  } else {
    shrd = nullptr;
  }
  return shrd;
}

inline void SmashChunks::SetNextMemoryForCompressionLibrary(
    std::shared_ptr<SmashMemory> memory, void *data,
    const uint32_t &data_size) {
  std::lock_guard<std::mutex> lock(mutex_for_compression_library_);
  memory->SetCompressionLibraryData(data);
  memory->SetCompressionLibraryDataSize(data_size);
  memory->SetStatus(SmashMemory::Status::ReadyForDecompression);
  condition_for_compression_library_.notify_one();
}

inline bool SmashChunks::SetNextMemoryForCompressionLibrary(
    void *data, const uint32_t &data_size) {
  bool status{true};
  // Just one thread
  {
    std::unique_lock<std::mutex> lock(mutex_for_communication_layer_);
    condition_for_communication_layer_.wait(lock, [this] {
      return (chunks_[first_available_to_set_]->GetStatus() ==
              SmashMemory::Status::Transferring) ||
             (chunks_[first_available_to_set_]->GetStatus() ==
              SmashMemory::Status::ReadyForCommunicationLayer) ||
             (chunks_[first_available_to_set_]->GetStatus() ==
              SmashMemory::Status::Error);
    });
  }
  std::shared_ptr<SmashMemory> memory = chunks_[first_available_to_set_];
  if (status = (memory->GetStatus() != SmashMemory::Status::Error)) {
    std::lock_guard<std::mutex> lock(mutex_for_compression_library_);
    memory->SetCompressionLibraryData(data);
    memory->SetCompressionLibraryDataSize(data_size);
    memory->SetStatus(SmashMemory::Status::ReadyForCompression);
    first_available_to_set_ = (++first_available_to_set_) % number_of_chunks_;
    condition_for_compression_library_.notify_one();
  }
  return status;
}

inline void SmashChunks::SetNextMemoryForCommunicationLayer(
    std::shared_ptr<SmashMemory> memory, const bool &status) {
  std::lock_guard<std::mutex> lock(mutex_for_communication_layer_);
  memory->SetStatus(status ? SmashMemory::Status::ReadyForCommunicationLayer
                           : SmashMemory::Status::Error);
  condition_for_communication_layer_.notify_one();
}

inline bool SmashChunks::Synchronize() {
  bool status{true};
  for (auto &memory : chunks_) {
    std::unique_lock<std::mutex> lock(mutex_for_communication_layer_);
    condition_for_communication_layer_.wait(lock, [memory] {
      return (memory->GetStatus() == SmashMemory::Status::Transferring) ||
             (memory->GetStatus() ==
              SmashMemory::Status::ReadyForCommunicationLayer) ||
             (memory->GetStatus() == SmashMemory::Status::Error);
    });
    status &= memory->GetStatus() != SmashMemory::Status::Error;
  }
  return status;
}

inline void SmashChunks::TheEnd() {
  for (auto &memory : chunks_) {
    std::unique_lock<std::mutex> lock(mutex_for_communication_layer_);
    condition_for_communication_layer_.wait(lock, [memory] {
      return (memory->GetStatus() == SmashMemory::Status::Transferring) ||
             (memory->GetStatus() ==
              SmashMemory::Status::ReadyForCommunicationLayer) ||
             (memory->GetStatus() == SmashMemory::Status::Error);
    });
    memory->SetStatus(SmashMemory::Status::End);
    condition_for_compression_library_.notify_one();
  }
}
