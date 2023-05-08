#ifndef TCP_SOCKET_HPP
#define TCP_SOCKET_HPP

#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#include "Address.hpp"
#include "Endpoint.hpp"
#include "Socket.hpp"

class TcpSocket : public Socket<TcpSocket>
{
  public:
    TcpSocket()
    {
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1)
        {
        }

        int optval = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    }

    ~TcpSocket()
    {
        close(sockfd);
    }

    void listen(int backlog)
    {
        if (::listen(sockfd, backlog) == -1)
        {
            throw std::runtime_error("Error listening on socket: " + std::string(strerror(errno)));
        }
    }

    TcpSocket accept()
    {
        int clientfd = ::accept(sockfd, nullptr, nullptr);
        if (clientfd == -1)
        {
            throw std::runtime_error("Error accepting connection: " + std::string(strerror(errno)));
        }
        return TcpSocket(clientfd);
    }

    void connect(Endpoint endpoint)
    {
        if (::connect(this->sockfd, (struct sockaddr *)endpoint.getSockaddr(), endpoint.getSockaddrSize()) == -1)
        {
            throw std::runtime_error("Error connecting to address: " + std::string(strerror(errno)));
        }
    }

    int getBoundPort()
    {
        sockaddr_in addr;
        socklen_t len = sizeof(addr);
        if (::getsockname(sockfd, (sockaddr *)&addr, &len) < 0)
        {
            throw std::runtime_error("Error getting bound address: " + std::string(strerror(errno)));
        }
        return htons(addr.sin_port);
    }

  private:
    TcpSocket(int sockfd)
    {
        this->sockfd = sockfd;
    }
};

#endif
