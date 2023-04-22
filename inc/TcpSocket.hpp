#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

class TCPSocket
{
  public:
    TCPSocket()
    {
        sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd_ == -1)
        {
            throw std::runtime_error("Error creating socket: " + std::string(strerror(errno)));
        }
    }

    ~TCPSocket()
    {
        close(sockfd_);
    }

    void bind(int port)
    {
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = INADDR_ANY;
        if (::bind(sockfd_, (sockaddr *)&addr, sizeof(addr)) == -1)
        {
            throw std::runtime_error("Error binding socket: " + std::string(strerror(errno)));
        }
    }

    void listen(int backlog)
    {
        if (::listen(sockfd_, backlog) == -1)
        {
            throw std::runtime_error("Error listening on socket: " + std::string(strerror(errno)));
        }
    }

    TCPSocket accept()
    {
        int clientfd = ::accept(sockfd_, nullptr, nullptr);
        if (clientfd == -1)
        {
            throw std::runtime_error("Error accepting connection: " + std::string(strerror(errno)));
        }
        return TCPSocket(clientfd);
    }

    void connect(const std::string &host, int port)
    {
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        inet_pton(AF_INET, host.c_str(), &addr.sin_addr);
        if (::connect(sockfd_, (sockaddr *)&addr, sizeof(addr)) == -1)
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
            int bytes_sent = ::send(sockfd_, buffer, len, 0);
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
        int bytes_recv = ::recv(sockfd_, buffer, max_len, 0);
        if (bytes_recv == -1)
        {
            throw std::runtime_error("Error receiving data: " + std::string(strerror(errno)));
        }
        return std::string(buffer, bytes_recv);
    }

  private:
    int sockfd_;

    TCPSocket(int sockfd) : sockfd_(sockfd)
    {
    }
};