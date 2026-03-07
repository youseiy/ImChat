//
// Created by theus on 07/09/2025.
//

#include "Client.h"
#include "ImChatLog.h"
#include "SFML/Network/IpAddress.hpp"
#include "SFML/Network/Packet.hpp"

namespace {
    std::string TrimAtFirstNull(const std::string& value) {
        const auto nullPos = value.find('\0');
        if (nullPos == std::string::npos) {
            return value;
        }
        return value.substr(0, nullPos);
    }
}

ImChat::Client::Client() {

}

ImChat::Client::~Client() {
    StopListeningServer();
    Loggout();
}

bool ImChat::Client::Login(const std::string& username, const std::string& password,
                                 const sf::IpAddress& serverIp, unsigned short port) {

    m_socket.setBlocking(true);

    // Connect to server

    if (m_socket.connect(serverIp, port,sf::seconds(2)) != sf::Socket::Status::Done) {
        ImChatLog::error("Failed to connect to server");
        return false;
    }

    // Send username
    sf::Packet packet;
    const std::string cleanUsername = TrimAtFirstNull(username);
    packet << cleanUsername;

    ImChatLog::warn("Logging in server with username {} and password {} \n", cleanUsername,password);

    if (m_socket.send(packet) != sf::Socket::Status::Done) {
         ImChatLog::error("Failed to send username");
        return false;
    }

    // Wait for server reply
    sf::Packet reply;
    if (m_socket.receive(reply) != sf::Socket::Status::Done) {
        ImChatLog::error("Failed to receive server reply");
        return false;
    }

    m_socket.setBlocking(false);

    std::string response;

    reply >> response;


    ImChatLog::warn("Sever response {}",response);


    StartListeningServer();

    return true;
}

void ImChat::Client::SendMessage(const std::string &message) {


}

void ImChat::Client::StartListeningServer() {

    m_server_listener_thread=std::jthread{&Client::listenServer, this};


}

void ImChat::Client::StopListeningServer() {

    m_server_listener_thread.request_stop();
}

void ImChat::Client::listenServer() {

    ImChatLog::info("Listening to server...");

    while (true) {
        // Wait for server reply
        sf::Packet reply;
        if (m_socket.receive(reply) == sf::Socket::Status::Done) {
            std::string response;

            reply >> response;

            ImChatLog::Connection::warn("Server response {}",response);
        }
    }
}

sf::TcpSocket &ImChat::Client::GetMutableTcpSocket() {
    return m_socket;
}

void ImChat::Client::Loggout() {
    m_socket.disconnect();
}
