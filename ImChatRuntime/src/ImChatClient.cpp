//
// Created by theus on 07/09/2025.
//

#include "ImChatClient.h"
#include <iostream>
#include "SFML/Network/IpAddress.hpp"
#include "SFML/Network/Packet.hpp"


ImChat::ImChatClient::ImChatClient() {

}

bool ImChat::ImChatClient::Login(const std::string& username, const std::string& password,
                                 const sf::IpAddress& serverIp, unsigned short port) {

    m_socket.setBlocking(true);

    // Connect to server



    if (m_socket.connect(serverIp, port,sf::seconds(2)) != sf::Socket::Status::Done) {
        std::cerr << "Failed to connect to server\n";
        return false;
    }


    // Send username
    sf::Packet packet;
    packet << username;

    std::cout << std::format("Logging in server with username {} and password {} \n", username,password);

    if (m_socket.send(packet) != sf::Socket::Status::Done) {
        std::cout << "Failed to send username\n";
        return false;
    }

    // Wait for server reply
    sf::Packet reply;
    if (m_socket.receive(reply) != sf::Socket::Status::Done) {
        std::cerr << "Failed to receive reply\n";
        return false;
    }
    m_socket.setBlocking(false);

    std::string response;

    reply >> response;

    std::cerr << response;

    return true;


}

sf::TcpSocket &ImChat::ImChatClient::GetMutableTcpSocket() {
    return m_socket;
}
