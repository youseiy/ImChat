//
// Created by theus on 16/08/2025.
//

#include "Login.h"

#if !IMCHAT_SERVER
bool ImChat::tryLogin(const std::string &username, const std::string &password, const sf::IpAddress &serverIp,
                      unsigned short port) {
    sf::TcpSocket socket;
    socket.setBlocking(false);
    if (socket.connect(serverIp, port) != sf::Socket::Status::Done) return false;

    sf::Packet packet;
    packet << username << password;
    if (socket.send(packet) != sf::Socket::Status::Done) return false;

    sf::Packet reply;
    if (socket.receive(reply) != sf::Socket::Status::Done) return false;

    bool success;
    reply >> success;
    return success;
}
#endif