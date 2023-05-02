/**
 * @file Endpoint.cpp
 */

#include "Endpoint.hpp"

/////////////////////////////////////////////////////////////////
Endpoint::Endpoint(const std::shared_ptr<Address> &addr, in_port_t port, InternetProtocol protocol)
    : addr(addr), port(port), protocol(protocol)
{
    this->addr->setPort(port);
}

/////////////////////////////////////////////////////////////////
void Endpoint::setAddress(const std::shared_ptr<Address> &addr)
{
    this->addr = addr;
}

/////////////////////////////////////////////////////////////////
void Endpoint::setPort(in_port_t port)
{
    this->port = port;
    this->addr->setPort(port);
}

/////////////////////////////////////////////////////////////////
const std::shared_ptr<Address> Endpoint::getAddress() const
{
    return this->addr;
}

/////////////////////////////////////////////////////////////////
in_port_t Endpoint::getPort() const
{
    return this->port;
}

/////////////////////////////////////////////////////////////////
InternetProtocol Endpoint::getProtocol() const
{
    return protocol;
}

/////////////////////////////////////////////////////////////////
const sockaddr *Endpoint::getSockaddr() const
{
    return addr->getSockaddr();
}
