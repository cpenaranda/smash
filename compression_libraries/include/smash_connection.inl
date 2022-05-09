/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <unistd.h>

inline int SmashConnection::WriteInternal(const char *const buffer,
                                          const uint32_t &number_bytes) {
  int len{0}, attempts{30}, data_sent{0};
  while (data_sent >= 0 && number_bytes - data_sent > 0) {
    len = write(socket_, buffer + data_sent, number_bytes - data_sent);
    if (len < 1) {
      if (errno == EAGAIN) {
        if (attempts) {
          --attempts;
          continue;
        }
      }
      data_sent = len;
    } else {
      data_sent += len;
    }
  }
  return data_sent;
}

inline int SmashConnection::Write(const char *const buffer,
                                  const uint32_t &number_bytes,
                                  const bool &ack) {
  int data_sent = WriteInternal(reinterpret_cast<const char *>(&number_bytes),
                                sizeof(number_bytes));
  if (data_sent > 0) {
    data_sent += WriteInternal(buffer, number_bytes);
  }
  if (ack) {
    bool status{false};
    ReadInternal(reinterpret_cast<char *>(&status), sizeof(status));
  }
  return data_sent;
}

inline int SmashConnection::ReadInternal(char *const buffer,
                                         const uint32_t &number_bytes) {
  int len{0}, attempts{30}, data_received{0};
  while (data_received >= 0 && number_bytes - data_received > 0) {
    len = read(socket_, buffer + data_received, number_bytes - data_received);
    if (len < 0) {
      if (errno == EAGAIN) {
        if (attempts) {
          --attempts;
          continue;
        }
      }
      data_received = len;
    } else {
      data_received += len;
    }
  }
  return data_received;
}

inline int SmashConnection::Read(char *const buffer, uint32_t *number_bytes,
                                 const bool &ack) {
  uint32_t bytes{0};
  int data_received =
      ReadInternal(reinterpret_cast<char *>(&bytes), sizeof(bytes));
  if (data_received > 0) {
    data_received += ReadInternal(buffer, bytes);
  }
  if (number_bytes) *number_bytes = bytes;
  if (ack) {
    bool status{true};
    WriteInternal(reinterpret_cast<char *>(&status), sizeof(status));
  }
  return data_received;
}

inline void SmashConnection::SetSocket(const int &socket) { socket_ = socket; }
