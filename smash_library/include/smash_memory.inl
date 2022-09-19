/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

inline char *SmashMemory::GetData() { return reinterpret_cast<char *>(data_); }

inline char *SmashMemory::GetCompressionLibraryData() {
  return reinterpret_cast<char *>(compression_library_data_);
}

inline void SmashMemory::SetCompressionLibraryData(void *data) {
  compression_library_data_ = data;
}

inline uint32_t SmashMemory::GetSize() { return size_; }

inline uint32_t SmashMemory::GetCompressionLibraryDataSize() {
  return compression_library_data_size_;
}

inline uint32_t SmashMemory::GetDecompressionLibraryDataSize() {
  return decompression_library_data_size_;
}

inline void SmashMemory::SetCompressionLibraryDataSize(
    const uint32_t &data_size) {
  compression_library_data_size_ = data_size;
}

inline void SmashMemory::SetDecompressionLibraryDataSize(
    const uint32_t &data_size) {
  decompression_library_data_size_ = data_size;
}

inline SmashMemory::Status SmashMemory::GetStatus() { return status_; }

inline void SmashMemory::SetStatus(const Status &status) { status_ = status; }
