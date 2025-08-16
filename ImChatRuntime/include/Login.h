//
// Created by theus on 16/08/2025.
//

#ifndef IMCHAT_LOGIN_H
#define IMCHAT_LOGIN_H
#include "SFML/Network/IpAddress.hpp"
#include "SFML/Network/Packet.hpp"
#include "SFML/Network/TcpSocket.hpp"

namespace ImChat {
#if !IMCHAT_SERVER
    bool tryLogin(const std::string& username, const std::string& password,
                             const sf::IpAddress& serverIp, unsigned short port);
#endif

}


#endif //IMCHAT_LOGIN_H