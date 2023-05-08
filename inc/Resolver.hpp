/**
 * @file Resolver.hpp
 */

#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#include "Address.hpp"
#include "AddressView.hpp"
#include "Ipv4Address.hpp"
#ifndef RESOLVER_HPP
#define RESOLVER_HPP

/**
 * @brief Resolves address with unspecified address types.
 */
class Resolver
{
  public:
    /// @brief Resolves a hostname into a vector of addresses.
    ///
    /// @param hostname The hostname to resolve.
    ///
    /// @return A vector of shared pointers to Address objects representing IPv4 addresses.
    static const std::vector<std::shared_ptr<Address>> resolve(std::string hostname)
    {
        struct addrinfo hints, *res, *i;
        std::memset(&hints, 0, sizeof(hints));

        std::vector<std::shared_ptr<Address>> addresses;

        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags |= AI_CANONNAME;

        int retval = getaddrinfo(hostname.c_str(), NULL, &hints, &res);
        if (retval == 0)
        {
            for (i = res; i != 0; i = i->ai_next)
            {
                if (i->ai_family == AF_INET)
                {
                    sockaddr_in *addr = reinterpret_cast<sockaddr_in *>(i->ai_addr);
                    addresses.emplace_back(std::make_shared<Ipv4Address>(*addr));
                }
                else
                {
                    /// @todo other
                }
            }
        }
        else
        {
            /// @todo, do gai stuff
            throw std::runtime_error("Error resolving address: " + std::string(strerror(errno)));
        }

        freeaddrinfo(res);

        return addresses;
    }
};

#endif
