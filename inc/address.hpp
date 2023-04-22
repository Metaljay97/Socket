#ifndef ADDRESS_H
#define ADDRESS_H

#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

class Address
{
  public:
    /// Constructor with a given IPv4 address.
    ///
    /// @param addr  The IPv4 address.
    Address(sockaddr_in addr) : addr(addr)
    {
        this->addr.sin_family = AF_INET;
        this->ip = Utils::binaryToAddress(addr.sin_addr);
    }

    static const std::vector<Address> Address::resolve(std::string hostname)
    {
        struct addrinfo hints, *res, *i;
        std::vector<Address> addresses;

        std::memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET; /// dealing only with ipv4 address for now...
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags |= AI_CANONNAME;

        int retval = getaddrinfo(hostname.c_str(), NULL, &hints, &res);
        if (retval == 0)
        {
            for (i = res; i != 0; i = i->ai_next)
            {
                struct sockaddr_in *addr = (struct sockaddr_in *)i->ai_addr;
                Address address(*addr);
                addresses.emplace_back(address);
            }
        }
        else
        {
            /// @todo, do gai stuff
            throw std::runtime_error("Error resolving address: " + std::string(strerror(errno)));
        }

        return addresses;
    }
    ////////////////////////////////////////////////////////////////////////////////
    bool Address::operator==(const Address &addr) const noexcept
    {
        return this->ip == addr.get();
    }

    ////////////////////////////////////////////////////////////////////////////////
    bool Address::operator!=(const Address &addr) const noexcept
    {
        return !(*this == addr);
    }

    ////////////////////////////////////////////////////////////////////////////////
    bool Address::operator<(const Address &addr) const noexcept
    {
        return this->ip < addr.get();
    }

    ////////////////////////////////////////////////////////////////////////////////
    bool Address::operator>(const Address &addr) const noexcept
    {
        return this->ip > addr.get();
    }

    ////////////////////////////////////////////////////////////////////////////////
    bool Address::operator<=(const Address &addr) const noexcept
    {
        return this->ip <= addr.get();
    }

    ////////////////////////////////////////////////////////////////////////////////
    bool Address::operator>=(const Address &addr) const noexcept
    {
        return this->ip >= addr.get();
    }

    ////////////////////////////////////////////////////////////////////////////////
    std::ostream &operator<<(std::ostream &out, const Address addr) noexcept
    {
        return out << addr.get();
    }

  protected:
    ////////////////////////////////////////////////////////////////////////////////
    inline const std::string Address::getAddr() const noexcept
    {
        return this->ip;
    }

    std::string ip;   ///< The IPv4 address.
    sockaddr_in addr; ///<  The addr struct
}
