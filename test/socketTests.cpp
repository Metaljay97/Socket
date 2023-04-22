/**
 * @file socketTests.cpp
 *
 * Unit tests for the exceptions class.
 */

#include <iostream>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "TcpSocket.hpp"

/// @addtogroup supporttests Unit Tests for the support compponents
/// @{

////////////////////////////////////////////////////////////////////////////////
/// Fixture for TcpSocket tests
////////////////////////////////////////////////////////////////////////////////
class TCPSocketTest : public ::testing::Test
{
  protected:
    /// Routines run before each tests
    virtual void SetUp()
    {
        socket = std::make_unique<TCPSocket>();
    }

    /// Routines run before each tests
    virtual void TearDown()
    {
        // Tear down the test fixture
        socket.reset();
    }

    std::unique_ptr<TCPSocket> socket; ///< The socket

    const int PORT = 8080; ///< The port to test on
};

TEST_F(TCPSocketTest, BindSocket)
{
    socket->bind(PORT);
    EXPECT_EQ(socket->getBoundPort(), PORT);
}

/// @}
