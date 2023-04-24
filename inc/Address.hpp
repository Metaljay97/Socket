/**
 * @file Address.hpp
 */

#ifndef ADDRESS_HPP
#define ADDRESS_HPP

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

class Endpoint; ///< Forward declaration of the endpoint class.

/**
 * @brief Address Interface, used represent an internet address.
 */
class Address
{
    friend class Endpoint; ///< To allow for manipulation of the internal sockaddr.

  public:
    /// Dtor
    virtual ~Address(){};
    /// @return the size of the address
    virtual socklen_t getSize() const = 0;
    /// @return the address family
    virtual sa_family_t getFamily() const = 0;

  protected:
    /// @brief Returns a const pointer to a sockaddr structure representing the address object.
    ///
    /// This function is set to protected to prevent access to the interal address struct to
    /// enforce an abstraction around it. It will be used by classes that will need the internal
    /// struct to complete operations, such as sockets classes.
    ///
    /// @returns the pointer to the sock address.
    virtual const sockaddr *getSockaddr() const = 0;

    /// @brief This method sets the port number of the internal address struct to the specified
    /// in_port_t value.
    ///
    /// This function is private because the design calls for a decoupling of an address and the
    /// port associated with it. The port should be accessed via an endpoint class.
    ///
    /// @param port An in_port_t value representing the port number.
    virtual void setPort(in_port_t port) = 0;
};

#endif
