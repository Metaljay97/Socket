/**
 * @file Ipv4Address.cpp
 */

#include "Ipv4Address.hpp"

/////////////////////////////////////////////////////////////////
explicit Ipv4Adress::Ipv4Address(const sockaddr_in &addr)
{
    std::memcpy(&this->addr, &addr, this->SIZE);
}

/////////////////////////////////////////////////////////////////
explicit Ipv4Adress::Ipv4Address(const sockaddr *addr)
{
    std::memcpy(&this->addr, addr, this->SIZE);
}

/////////////////////////////////////////////////////////////////
static const std::vector<std::shared_ptr<Address>> Ipv4Adress::resolve(std::string hostname)
{
    struct addrinfo hints, *res, *i;
    std::vector<std::shared_ptr<Address>> addresses;

    hints.ai_family = ADDRESS_FAMILY;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags |= AI_CANONNAME;

    int retval = getaddrinfo(hostname.c_str(), NULL, &hints, &res);
    if (retval == 0)
    {
        for (i = res; i != 0; i = i->ai_next)
        {
            sockaddr_in *addr = reinterpret_cast<sockaddr_in *>(i->ai_addr);
            addresses.emplace_back(std::make_shared<Ipv4Address>(*addr));
        }
    }
    else
    {
        /// @todo, do gai stuff
        throw std::runtime_error("Error resolving address: " + std::string(strerror(errno)));
    }

    return addresses;
}

/////////////////////////////////////////////////////////////////
virtual socklen_t Ipv4Adress::getSize() const override
{
    return this->SIZE;
}

/////////////////////////////////////////////////////////////////
virtual sa_family_t Ipv4Adress::getFamily() const override
{
    return ADDRESS_FAMILY;
}

/////////////////////////////////////////////////////////////////
virtual void Ipv4Adress::setPort(in_port_t port) override
{
    addr.sin_port = htons(port);
}

/////////////////////////////////////////////////////////////////
virtual const sockaddr *Ipv4Adress::getSockaddr() const override
{
    return reinterpret_cast<const sockaddr *>(&this->addr);
}
