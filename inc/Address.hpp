#ifndef ADDRESS_H
#define ADDRESS_H

#ifdef _WIN32
/// @todo, windows support
#else
#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#endif

class AddressInterface
{
  public:
    virtual ~AddressInterface(){};
    virtual socklen_t getSize() = 0;
    virtual const sockaddr *getSockaddr() = 0;
    virtual std::string toString() const = 0;
};

class Address : public AddressInterface
{
  public:
    Address(const sockaddr *addr, socklen_t size) : size(size)
    {

        std::memcpy(&this->addr, addr, this->size);
    }
    virtual ~Address(){};
    virtual socklen_t getSize()
    {
        return this->size;
    }
    virtual const sockaddr *getSockaddr()
    {
        return reinterpret_cast<const sockaddr *>(&this->addr);
    }
    virtual std::string toString() const
    {
    }

  private:
    sockaddr_storage addr; ///< The address
    socklen_t size;        ///< The size of the address
};

/*
class Ipv4Address
{
  public:
    /// Constructor with a given IPv4 address.
    ///
    /// @param addr  The IPv4 address.
    Address(sockaddr_in addr)
    {
    }

    static const std::vector<Address> Address::resolve(std::string hostname)
    {
        struct addrinfo hints, *res, *i;
        std::vector<Address> addresses;

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

  protected:
    std::string ip;   ///< The IPv4 address.
    sockaddr_in addr; ///<  The addr struct
}
*/
#endif
