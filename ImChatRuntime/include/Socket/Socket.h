#pragma once
#include "IpAdress.h"


class ISocket {
public:
    virtual ~ISocket() = default;

    virtual bool connect(const ImChat::IpAdress& ip, unsigned short port) = 0;
    virtual void disconnect() = 0;

    virtual bool send(const void* data, std::size_t size) = 0;
    virtual bool receive(std::vector<uint8_t>& buffer) = 0;
};
