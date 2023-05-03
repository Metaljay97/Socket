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
        if (::connect(this->sockfd, endpoint.getSockaddr(), sizeof(endpoint.getSockaddr())) == -1)
        {
            throw std::runtime_error("Error connecting to server: " + std::string(strerror(errno)));
        }
    }

    void send(const std::string &data)
    {
        const char *buffer = data.c_str();
        int len = data.length();
        while (len > 0)
        {
            int bytes_sent = ::send(sockfd, buffer, len, 0);
            if (bytes_sent == -1)
            {
                throw std::runtime_error("Error sending data: " + std::string(strerror(errno)));
            }
            buffer += bytes_sent;
            len -= bytes_sent;
        }
    }

    std::string recv(int max_len)
    {
        char buffer[max_len];
        int bytes_recv = ::recv(sockfd, buffer, max_len, 0);
        if (bytes_recv < 0)
        {
            throw std::runtime_error("Error receiving data: " + std::string(strerror(errno)));
        }
        return std::string(buffer, bytes_recv);
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
    in_port_t sockfd;

    TcpSocket(int sockfd) : sockfd(sockfd)
    {
    }
};
