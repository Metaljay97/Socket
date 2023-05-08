/**
 * @file socketTests.cpp
 *
 * Unit tests for the exceptions class.
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <atomic>
#include <condition_variable>
#include <iostream>
#include <string>
#include <thread>

#include "Address.hpp"
#include "Endpoint.hpp"
#include "Resolver.hpp"
#include "Socket.hpp"
#include "TcpSocket.hpp"

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
    for (const std::shared_ptr<Address> &address : addresses)
    {
        // Check if the address is not nullptr
        ASSERT_TRUE(address);

        // Check if the address is of type Ipv4Address
        ASSERT_TRUE(dynamic_cast<const Ipv4Address *>(address.get()) != nullptr);
    }
}

TEST_F(ResolverTest, ResolveNonExistantHostname)
{
    // Test input hostname
    const char *const HOSTNAME = "adlkj;alskdjfa;slkfja;lsdkjf";

    // Resolve the hostname
    ASSERT_THROW(Resolver::resolve(HOSTNAME), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////
/// Fixture for Ipv4Address tests
////////////////////////////////////////////////////////////////////////////////
class Ipv4AddressTest : public ::testing::Test
{

  protected:
    /// Routines run before each testsstd::shared_ptr<
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
/// Fixture for Ipv4Address tests
////////////////////////////////////////////////////////////////////////////////
class EndpointTest : public ::testing::Test
{

  protected:
    /// Routines run before each tests
    virtual void SetUp()
    {
        const constexpr char *HOSTNAME = "127.0.0.1";
        const std::vector<std::shared_ptr<Address>> localAddresses = Resolver::resolve(HOSTNAME);
        localAddr = localAddresses[0];

        const constexpr char *GOOGLE = "www.google.com";
        const std::vector<std::shared_ptr<Address>> googleAddresses = Resolver::resolve(GOOGLE);
        localAddr = googleAddresses[0];
    }

    std::shared_ptr<Address> localAddr;  ///< The sockaddr
    std::shared_ptr<Address> googleAddr; ///< The sockaddr
};

// Test case for setting and getting address
TEST_F(EndpointTest, SetGetAddress)
{
    // Create an Endpoint object
    Endpoint endpoint(localAddr, 1234, InternetProtocol::TCP);

    // Check that the initial address is correctly set
    EXPECT_EQ(endpoint.getAddress(), localAddr);

    // Create a new address

    // Set the new address
    endpoint.setAddress(googleAddr);

    // Check that the address is updated
    // EXPECT_EQ(endpoint.getAddress(), std::make_shared<Address>(newAddress));
}

// Test case for setting and getting port
TEST_F(EndpointTest, SetGetPort)
{
    // Create an Endpoint object
    Endpoint endpoint(localAddr, 1234, InternetProtocol::TCP);

    // Check that the initial port is correctly set
    EXPECT_EQ(endpoint.getPort(), 1234);

    // Set a new port
    endpoint.setPort(5678);

    // Check that the port is updated
    EXPECT_EQ(endpoint.getPort(), 5678);
}

// Test case for getting protocol
TEST_F(EndpointTest, GetProtocol)
{
    // Create an Endpoint object
    Endpoint endpoint(localAddr, 1234, InternetProtocol::TCP);

    // Check that the protocol is correctly set
    EXPECT_EQ(endpoint.getProtocol(), InternetProtocol::TCP);
}

////////////////////////////////////////////////////////////////////////////////
/// Fixture for TcpSocket tests
////////////////////////////////////////////////////////////////////////////////
class TcpSocketTest : public ::testing::Test
{
  protected:
    /// Routines run before each tests
    virtual void SetUp()
    {
        socket = std::make_unique<TcpSocket>();
    }

    /// Routines run before each tests
    virtual void TearDown()
    {
        // Tear down the test fixture
        socket.reset();
    }

    std::unique_ptr<TcpSocket> socket; ///< The socket
    static constexpr const char *const LOCAL_HOSTNAME = "localhost";
    const in_port_t PORT = 1024; ///< The port to test on
    std::shared_ptr<Address> LOCALHOST = Resolver::resolve(LOCAL_HOSTNAME)[0];
};

TEST_F(TcpSocketTest, ListenAndAccept)
{
    std::mutex mtx;
    std::condition_variable cv;

    std::thread accept_thread([this, &cv]() {
        try
        {
            TcpSocket serverSocket;
            serverSocket.isBlocking(true);
            serverSocket.bind(PORT);
            serverSocket.listen(5);
            cv.notify_all();
            TcpSocket acceptedSocket = serverSocket.accept();
        }
        catch (std::exception &e)
        {
            FAIL() << e.what();
        }
    });

    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock);

    TcpSocket clientSocket;
    clientSocket.connect(Endpoint(LOCALHOST, PORT, InternetProtocol::TCP));
    accept_thread.join();
}

TEST_F(TcpSocketTest, GetBoundPort)
{
    TcpSocket socket;
    socket.bind(PORT);

    int port = socket.getBoundPort();

    // Assert that the returned port matches the expected value
    EXPECT_EQ(port, PORT);
}
/// @}
