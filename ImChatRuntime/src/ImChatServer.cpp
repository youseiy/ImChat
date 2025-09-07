//
// Created by theus on 16/08/2025.
//

#include "ImChatServer.h"

#include <iostream>
#include <bits/fs_fwd.h>

#include "UserManager.h"
#include "SFML/Network/Packet.hpp"
#include "SFML/Network/TcpListener.hpp"

#if !IMCHAT_SERVER

namespace ImChat {
    ImChatServer::ImChatServer() {

        listener.setBlocking(false);
    }



    void ImChatServer::runServer(unsigned short port, std::atomic<bool>& running) {

        if (listener.listen(port) != sf::Socket::Status::Done) {
            std::cerr << "Failed to start server on port " << port << "\n";
            return; // Exit if the port is unavailable
        }
        m_selector.add(listener);

        while (running) {
            // Wait until one of the sockets is ready
            if (m_selector.wait()) {
                // Check if the listener (for new connections) wants to receive data i.e. Ready
                if (m_selector.isReady(listener)) {
                    receiveClientConnection();
                }
            }else {
                receiveClientData();
            }
        }

    }

    void ImChatServer::receiveClientConnection() {

        std::shared_ptr<sf::TcpSocket > IncomingSocket{std::make_shared<sf::TcpSocket>()};
        listener.accept(*IncomingSocket);

        // Receive an initial packet from the client
        sf::Packet packet;
        std::string msg;
        if (IncomingSocket->receive(packet) == sf::Socket::Status::Done) {
            packet >>msg;
        }

        std::cout << msg << "has connected to Server";

        m_selector.add(*IncomingSocket);
    }

    void ImChatServer::receiveClientData() {

        for (auto it = ClientSockets.begin(); it != ClientSockets.end(); ) {

            auto& clientSocket = *it;

            if (m_selector.isReady(*it->get())) {
                sf::Packet packet, sendPacket;

                if (clientSocket->receive(packet) == sf::Socket::Status::Done) {
                    std::cout << "Received packet with "<<packet.getDataSize()<<" bytes";
                    std::string text;
                    packet >> text;
                    sendPacket << text;
                    for (auto& client: ClientSockets) {

                        if (client!=clientSocket) {
                            client->send(packet);
                        }
                    }
                }
            }
        }
    }
}

#endif
