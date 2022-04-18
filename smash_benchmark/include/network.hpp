/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#pragma once

#include <iostream>

class Network {
 private:
  enum class ACK : char {
    SUCCESS,
    FAIL,
  };

 public:
  int socket_id;
  void CloseSocket(const int &socket);

  bool RecvACK();
  bool SendACK(const bool &value);

  bool SendBuffer(const char *buffer, const uint64_t &buffer_size,
                  const bool &ACK = false);

  bool RecvBuffer(char *buffer, uint64_t buffer_size, const bool &ACK = false);

  Network();
  virtual ~Network();
};
