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

// SMASH LIBRARIES
#include <network_server.hpp>

bool NetworkServer::InitializeServer(const int &port) {
  bool status = true;
  struct sockaddr_in address;
  // Creating socket file descriptor
  if ((socket_server = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    std::cout << "Error creating the main socket" << std::endl;
    status = false;
  } else {
    int opt{1};
    if (setsockopt(socket_server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
      std::cout << "Error configuring the scoket" << std::endl;
      status = false;
    } else {
      bzero(reinterpret_cast<char *>(&address), sizeof(address));
      address.sin_family = AF_INET;
      address.sin_addr.s_addr = INADDR_ANY;
      address.sin_port = htons(port);
      if (bind(socket_server, reinterpret_cast<struct sockaddr *>(&address),
               sizeof(address)) < 0) {
        std::cout << "Error binding the socket" << std::endl;
        status = false;
      }
    }
  }
  return status;
}

bool NetworkServer::GetNewConnection() {
  bool status{true};
  CloseSocket(socket_id);
  struct sockaddr_in address;
  int addrlen{sizeof(address)};
  if (listen(socket_server, 50) < 0) {
    std::cout << "Error listening new connections" << std::endl;
    status = false;
  } else {
    if ((socket_id = accept(socket_server,
                            reinterpret_cast<struct sockaddr *>(&address),
                            reinterpret_cast<socklen_t *>(&addrlen))) < 0) {
      std::cout << "Error accepting new connections" << std::endl;
      status = false;
    } else {
      SendACK(true);
    }
  }
  return status;
}

NetworkServer::NetworkServer() { socket_server = -1; }
NetworkServer::~NetworkServer() { CloseSocket(socket_server); }
