/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#pragma once

#include <iostream>

class SmashConnection {
 private:
  int socket_;

  int WriteInternal(const char *const buffer, const uint32_t &number_bytes);

  int ReadInternal(char *const buffer, const uint32_t &number_bytes);

 public:
  int Write(const char *const buffer, const uint32_t &number_bytes,
            const bool &ack = false);

  int Read(char *const buffer, uint32_t *number_bytes, const bool &ack = false);

  void SetSocket(const int &socket);

  SmashConnection();
  ~SmashConnection();
};

#include <smash_connection.inl>  // NOLINT
