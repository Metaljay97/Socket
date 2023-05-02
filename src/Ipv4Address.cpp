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
