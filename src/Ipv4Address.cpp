/**
 * @file Ipv4Address.cpp
 */

#include "Ipv4Address.hpp"

/////////////////////////////////////////////////////////////////
Ipv4Address::Ipv4Address(const sockaddr_in &addr)
{
    std::memcpy(&this->addr, &addr, this->SIZE);
}

/////////////////////////////////////////////////////////////////
Ipv4Address::Ipv4Address(const sockaddr *addr)
{
    std::memcpy(&this->addr, addr, this->SIZE);
}

/////////////////////////////////////////////////////////////////
socklen_t Ipv4Address::getSize() const
{
    return this->SIZE;
}

/////////////////////////////////////////////////////////////////
sa_family_t Ipv4Address::getFamily() const
{
    return ADDRESS_FAMILY;
}

/////////////////////////////////////////////////////////////////
void Ipv4Address::setPort(in_port_t port)
{
    addr.sin_port = htons(port);
}

/////////////////////////////////////////////////////////////////
const sockaddr *Ipv4Address::getSockaddr() const
{
    return reinterpret_cast<const sockaddr *>(&this->addr);
}
