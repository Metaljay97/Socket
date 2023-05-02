/**
 * @file Ipv4Address.hpp
 */

#ifndef IPV4_ADDRESS_H
#define IPV4_ADDRESS_H

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

#include "Address.hpp"
/**
 * @brief The Ipv4Address class represents an IPv4 address.
 */
class Ipv4Address : public Address
{
  public:
    /// @brief Ctor constructs an Ipv4 address form a sockaddr_in struct
    ///
    /// @param addr A reference to the sockaddr_in struct used to construct and address from
    explicit Ipv4Address(const sockaddr_in &addr);

    /// @brief Ctor constructs an Ipv4 address form a sockaddr struct
    ///
    /// @param addr A reference to the sockaddr struct used to construct and address from
    explicit Ipv4Address(const sockaddr *addr);

    /// @copydoc Addres::getSize()
    virtual socklen_t getSize() const override;

    /// @copydoc Address::getFamily()
    virtual sa_family_t getFamily() const override;
    /// Dtor
    virtual ~Ipv4Address(){};

    static constexpr sa_family_t ADDRESS_FAMILY = AF_INET; ///< The family address for this socket.

  protected:
    sockaddr_in addr; ///< The internal sockaddr_in this object is wrapping around

    static constexpr socklen_t SIZE = static_cast<socklen_t>(sizeof(sockaddr_in)); ///< The addr struct size

    /// @copydoc Address::getFamily()
    virtual void setPort(in_port_t port) override;

    /// @copydoc Address::getSockaddr()
    virtual const sockaddr *getSockaddr() const override;
};

#endif
