/**
 * @file Endpoint.hpp
 */

#ifndef ENDPOINT_HPP
#define ENDPOINT_HPP

#ifdef _WIN32
/// @todo, windows support
#else
#include <arpa/inet.h>
#include <cstring>
#include <memory>
#include <netdb.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#endif

#include "Address.hpp"
#include "AddressView.hpp"
#include "InternetProtocol.h"

/**
 * @brief Represents a network endpoint with an address, port, and protocol.
 *
 * An Endpoint object encapsulates a network address, port, and protocol, and provides
 * methods to access and modify these attributes.
 */
class Endpoint
{
  public:
    /// @brief Constructs a new Endpoint object with the specified address, port, and protocol.
    ///
    /// The constructor initializes the Endpoint object with a shared pointer to an Address View,
    /// an in_port_t value representing the port number, and a Protocol value representing the protocol.
    ///
    /// @param addr A shared pointer to an Address object representing the network address.
    /// @param port An in_port_t value representing the port number.
    /// @param protocol A InternetProtocol value representing the protocol.
    /// @tparam ADDR_T The type of the address
    Endpoint(const std::shared_ptr<Address> &addr, in_port_t port, InternetProtocol protocol)
        : addr(std::move(addr)), port(port), protocol(protocol)
    {
        this->addr->setPort(port);
    }

    /// @brief Sets the network address of the Endpoint object.
    ///
    /// This method sets the network address of the Endpoint object to the specified shared pointer
    /// to an Address object.
    ///
    /// @param addr A shared pointer to an Address object representing the network address.
    /// @tparam ADDR_T The type of the address
    void setAddress(const std::shared_ptr<Address> &addr)
    {
        this->addr = std::move(addr);
    }
    /// @brief Sets the port number of the Endpoint object.
    ///
    /// This method sets the port number of the Endpoint object to the specified in_port_t value,
    /// and updates the port number of the Address object encapsulated by the Endpoint object.
    ///
    /// @param port An in_port_t value representing the port number.
    void setPort(in_port_t port);

    /// @brief Returns the network address of the Endpoint object.
    ///
    /// This method returns a shared pointer to the Address object representing the network address
    /// encapsulated by the Endpoint object.
    ///
    /// @return A shared pointer to an Address object representing the network address.
    const std::shared_ptr<Address> getAddress() const;

    /// @brief Returns the port number of the Endpoint object.
    ///
    /// This method returns the in_port_t value representing the port number of the Endpoint object.
    ///
    /// @return An in_port_t value representing the port number.
    in_port_t getPort() const;

    /// @brief Returns the protocol of the Endpoint object.
    ///
    /// This method returns the Protocol value representing the protocol of the Endpoint object.
    ///
    /// @return A Protocol value representing the protocol.
    InternetProtocol getProtocol() const;

    /// @brief Returns a const pointer to a sockaddr structure representing the Endpoint object.
    ///
    /// This method returns a const pointer to a sockaddr structure representing the network endpoint
    /// encapsulated by the Endpoint object.
    ///
    /// @return A const pointer to a sockaddr structure representing the Endpoint object.
    const sockaddr *getSockaddr() const;

    const socklen_t getSockaddrSize() const
    {
        return addr->getSize();
    }

  protected:
    std::shared_ptr<Address> addr; ///< A shared pointer to an Address object representing the network address.
    in_port_t port;                ///< An in_port_t value representing the port number.
    InternetProtocol protocol;     ///< A Protocol value representing the protocol.
};

#endif
