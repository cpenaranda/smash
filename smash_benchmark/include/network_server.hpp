/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#pragma once

#include <string>

// SMASH LIBRARIES
#include <network.hpp>

class NetworkServer : public Network {
 private:
  int socket_server;

 public:
  bool InitializeServer(const int &port);
  bool GetNewConnection();

  NetworkServer();
  ~NetworkServer();
};
