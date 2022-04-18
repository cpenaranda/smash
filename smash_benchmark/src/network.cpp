/*
 * rCUDA: remote CUDA (www.rCUDA.net)
 * Copyright (C) 2016-2022
 * Grupo de Arquitecturas Paralelas
 * Departamento de Informática de Sistemas y Computadores
 * Universidad Politécnica de Valencia (Spain)
 */

#include <netdb.h>  // getaddrinfo, freeaddrinfo
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <string>

// SMASH LIBRARIES
#include <network.hpp>

void Network::CloseSocket(const int &socket) {
  if (socket > 0) {
    close(socket);
  }
}

bool Network::RecvACK() {
  ACK ok = ACK::FAIL;
  bool status = RecvBuffer(reinterpret_cast<char *>(&ok), sizeof(ok));
  return status && ok == ACK::SUCCESS;
}

bool Network::SendACK(const bool &value) {
  ACK ok = value ? ACK::SUCCESS : ACK::FAIL;
  bool status = SendBuffer(reinterpret_cast<char *>(&ok), sizeof(ok));
  return status;
}

bool Network::SendBuffer(const char *buffer, const uint64_t &buffer_size,
                         const bool &ACK) {
  int len = 0;
  int attempts = 30;
  bool status = true;
  uint64_t data_sent = 0;
  while (buffer_size - data_sent > 0 && status) {
    len = write(socket_id, buffer + data_sent, buffer_size - data_sent);
    if (len < 1) {
      if (errno == EAGAIN) {
        if (attempts) {
          --attempts;
          continue;
        }
      }
      std::cout << "Error writing data (errno " << errno << ")" << std::endl;
      status = false;
    }
    data_sent += len;
  }
  if (status && ACK) {
    status = RecvACK();
  }
  return status;
}

bool Network::RecvBuffer(char *buffer, uint64_t buffer_size, const bool &ACK) {
  int len = 0;
  int attempts = 30;
  bool status = true;
  uint64_t data_received = 0;
  while (buffer_size - data_received > 0 && status) {
    len = read(socket_id, buffer + data_received, buffer_size - data_received);
    if (len < 0) {
      if (errno == EAGAIN) {
        if (attempts) {
          --attempts;
          continue;
        }
      }
      std::cout << "Error receiving data (errno " << errno << ")" << std::endl;
      status = false;
    }
    if (len == 0) {
      std::cout << "Connection closed" << std::endl;
      status = false;
    }
    data_received += len;
  }
  if (ACK) {
    status = SendACK(status);
  }
  return status;
}

Network::Network() { socket_id = -1; }

Network::~Network() { CloseSocket(socket_id); }
