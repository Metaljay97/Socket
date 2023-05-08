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
#include "Ipv4Address.hpp"

#ifndef ADDRESS_VIEW_HPP
#define ADDRESS_VIEW_HPP

/**
 * @brief Address View, used to view address objects via type erasure.
 */
class AddressView : public Address
{
    friend class Endpoint; ///< To allow for manipulation of the internal sockaddr.

  public:
    /**
     * This constructs an address view via an address object.
     *
     * @param address The address to construct the view from.
     * @tparam Addr The address type
     */
    template <typename Addr> explicit AddressView(const Addr &address) : Address(std::make_shared<Address>(address))
    {
    }

    /// Dtor
    virtual ~AddressView(){};

    /// @return the size of the address
    virtual socklen_t getSize() const override
    {
        return addr->getSize();
    }

    /// @return the address family
    virtual sa_family_t getFamily() const override
    {
        return addr->getFamily();
    }

    virtual const Address *get()
    {
        return addr.get();
    }

  protected:
    /// @brief Returns a const pointer to a sockaddr structure representing the address object.
    ///
    /// This function is set to protected to prevent access to the interal address struct to
    /// enforce an abstraction around it. It will be used by classes that will need the internal
    /// struct to complete operations, such as sockets classes.
    ///
    /// @returns the pointer to the sock address.
    virtual const sockaddr *getSockaddr() const override
    {
        return addr->getSockaddr();
    }

    /// @brief This method sets the port number of the internal address struct to the specified
    /// in_port_t value.
    ///
    /// This function is private because the design calls for a decoupling of an address and the
    /// port associated with it. The port should be accessed via an endpoint class.
    ///
    /// @param port An in_port_t value representing the port number.
    virtual void setPort(in_port_t port) override
    {
        addr->setPort(port);
    }

    const std::shared_ptr<Address> addr; ///< The interal address object.
};

#endif
