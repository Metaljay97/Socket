#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <poll.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#include "Address.hpp"
#include "Endpoint.hpp"

enum class PollResult
{
    INCOMING_DATA,
    INCOMING_CONNECTION,
    OTHER ///< to be removed later
};

template <class Derived> class Socket
{
  public:
    void send(const void *buffer, size_t len)
    {
        int bytes_sent = ::send(sockfd, buffer, len, 0);
        if (bytes_sent == -1)
        {
            throw std::runtime_error("Error sending data: " + std::string(strerror(errno)));
        }
    }

    template <typename T> void send(T data)
    {
        static_assert(std::is_fundamental<T>::value, "error message");
        send((char *)data, sizeof(data));
    }

    void send(const std::string &data)
    {
        send(data.c_str(), data.length());
    }

    char *recv(int max_len, int *size)
    {
        char buffer[max_len];
        int bytes_recv = ::recv(sockfd, buffer, max_len, 0);
        if (bytes_recv < 0)
        {
            throw std::runtime_error("Error receiving data: " + std::string(strerror(errno)));
        }
        *size = bytes_recv;
        return buffer;
    }

    PollResult poll(int timeoutMillis = -1)
    {
        struct pollfd fds[1];
        fds[0].fd = sockfd;
        fds[0].events = POLLIN | POLLOUT;

        int ready = ::poll(fds, 1, timeoutMillis);
        if (ready == -1)
        {
            // handle error
        }

        if (fds[0].revents & POLLIN)
        {
            if (fds[0].fd == sockfd)
            {
                return PollResult::INCOMING_CONNECTION;
            }
            else
            {
                return PollResult::INCOMING_DATA;
            }
        }
        else
        {
            return PollResult::OTHER;
        }
    }

    void setBlocking(bool blocking)
    {
#ifdef _WIN32
        unsigned long mode = blocking ? 0 : 1;
        return ioctlsocket(sockfd, FIONBIO, &mode) == 0;
#else
        int flags = fcntl(sockfd, F_GETFL, 0);
        if (flags == -1)
        {
            // handle errors
        }

        flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
        fcntl(sockfd, F_SETFL, flags); // handle errors
#endif
    }

    void bind(in_port_t port)
    {
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = INADDR_ANY;
        if (::bind(sockfd, (sockaddr *)&addr, sizeof(addr)) == -1)
        {
            throw std::runtime_error("Error binding socket: " + std::string(strerror(errno)));
        }
    }

    virtual ~Socket()
    {
        close(sockfd);
    }

  private:
    in_port_t sockfd;
};
