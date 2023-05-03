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

class UdpSocket : public Socket<TcpSocket>
{
  public:
    UdpSocket()
    {
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd == -1)
        {
        }
    }

    ~UdpSocket();
};
