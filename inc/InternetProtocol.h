/**
 * @file InternetProtocol.h
 */

#ifndef INTERNET_PROTOCOL_H
#define INTERNET_PROTOCOL_H

/**
 * @brief Possible internet protocols that can be used for communication.
 */
enum class InternetProtocol
{
    TCP = IPPROTO_TCP, ///< Transmission Control Protocol
    UDP = IPPROTO_UDP  ///< User Datagram Protocol
};
#endif
