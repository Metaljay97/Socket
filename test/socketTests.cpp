/**
 * @file socketTests.cpp
 *
 * Unit tests for the exceptions class.
 */

#include <iostream>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

//#include "TcpSocket.hpp"
#include "Address.hpp"
#include "Resolver.hpp"

/// @addtogroup supporttests Unit Tests for the support compponents
/// @{

////////////////////////////////////////////////////////////////////////////////
/// Fixture for TcpSocket tests
////////////////////////////////////////////////////////////////////////////////
class ResolverTest : public ::testing::Test
{
};

TEST_F(ResolverTest, ResolveHostname)
{
    // Test input hostname
    constexpr const char *HOSTNAME = "example.com";

    // Resolve the hostname
    std::vector<std::shared_ptr<Address>> addresses = Resolver::resolve(HOSTNAME);

    // Perform assertions on the resolved addresses
    ASSERT_FALSE(addresses.empty());
    for (const auto &address : addresses)
    {
        // Check if the address is not nullptr
        ASSERT_TRUE(address);

        // Check if the address is of type Ipv4Address
        ASSERT_TRUE(dynamic_cast<Ipv4Address *>(address.get()) != nullptr);
    }
}

TEST_F(ResolverTest, ResolveNonExistantHostname)
{
    // Test input hostname
    constexpr const char *HOSTNAME = "adlkj;alskdjfa;slkfja;lsdkjf";

    // Resolve the hostname
    ASSERT_THROW(std::vector<std::shared_ptr<Address>> addresses = Resolver::resolve(HOSTNAME), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////
/// Fixture for Ipv4Address tests
////////////////////////////////////////////////////////////////////////////////
class Ipv4AddressTest : public ::testing::Test
{

  protected:
    /// Routines run before each tests
    virtual void SetUp()
    {
        sockaddr_in sockaddr;
        std::memset(&sockaddr, 0, sizeof(sockaddr));

        // Set up the address information
        sockaddr.sin_family = AF_INET;
        sockaddr.sin_port = htons(8080);
        sockaddr.sin_addr.s_addr = inet_addr("192.168.0.1");
    }

    sockaddr_in sockaddr; ///< The sockaddr
};

TEST_F(Ipv4AddressTest, GetSize)
{
    Ipv4Address ipv4Address(sockaddr);
    socklen_t size = ipv4Address.getSize();
    ASSERT_EQ(size, sizeof(sockaddr_in));
}

TEST_F(Ipv4AddressTest, GetFamily)
{
    Ipv4Address ipv4Address(sockaddr);
    sa_family_t family = ipv4Address.getFamily();
    ASSERT_EQ(family, AF_INET);
}

////////////////////////////////////////////////////////////////////////////////
/// Fixture for TcpSocket tests
////////////////////////////////////////////////////////////////////////////////
class TCPSocketTest : public ::testing::Test
{
  protected:
    /// Routines run before each tests
    virtual void SetUp()
    {
        // socket = std::make_unique<TCPSocket>();
    }

    /// Routines run before each tests
    virtual void TearDown()
    {
        // Tear down the test fixture
        // socket.reset();
    }

    // std::unique_ptr<TCPSocket> socket; ///< The socket

    const int PORT = 8080; ///< The port to test on
};

TEST_F(TCPSocketTest, BindSocket)
{
    // socket->bind(PORT);
    //  EXPECT_EQ(socket->getBoundPort(), PORT);
}

/// @}
