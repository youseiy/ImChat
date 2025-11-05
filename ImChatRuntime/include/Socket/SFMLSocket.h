#pragma once

#include "Socket/Socket.h"


namespace ImChat {

    class SFMLSocket : public ISocket {

        bool connect(const ImChat::IpAdress &ip, unsigned short port) override;

    };
}