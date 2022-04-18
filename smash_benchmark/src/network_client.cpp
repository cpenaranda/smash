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
#include <network_client.hpp>

bool NetworkClient::CreateConnection(const int &port,
                                     const std::string &address) {
  bool status = true;
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  // Get the address of the server
  struct addrinfo *server_info;
  if (getaddrinfo(address.data(), std::to_string(port).data(), &hints,
                  &server_info) != 0) {
    std::cout << "Error getting the address info" << std::endl;
    status = false;
  } else {
    socket_id = socket(server_info->ai_family, server_info->ai_socktype,
                       server_info->ai_protocol);
    if (socket_id < 0) {
      std::cout << "Error creating the socket" << std::endl;
      status = false;
    } else {
      if (connect(socket_id, server_info->ai_addr, server_info->ai_addrlen) <
          0) {
        std::cout << "Error client could not connect to remote host"
                  << std::endl;
        status = false;
      } else {
        // At this point, the connection is successfully established
        freeaddrinfo(server_info);
        int on = 1;
        if (setsockopt(socket_id, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on)) !=
            0) {
          std::cout << "Could not set socket option" << std::endl;
          status = false;
        } else {
          if (setsockopt(socket_id, SOL_SOCKET, SO_KEEPALIVE, &on,
                         sizeof(on)) != 0) {
            std::cout << "Could not set socket option" << std::endl;
            status = false;
          } else {
            struct timeval tout;
            tout.tv_sec = 0;
            tout.tv_usec = 100000;
            if (setsockopt(socket_id, SOL_SOCKET, SO_RCVTIMEO, &tout,
                           sizeof(tout)) != 0) {
              std::cout << "Could not set socket option" << std::endl;
              status = false;
            } else {
              // Read the server has been connected correctly
              if (!RecvACK()) {
                std::cout << "Server has not been connected correctly"
                          << std::endl;
                status = false;
              }
            }
          }
        }
      }
    }
  }
  return status;
}

NetworkClient::NetworkClient() {}

NetworkClient::~NetworkClient() {}
