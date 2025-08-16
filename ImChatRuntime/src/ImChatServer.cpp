//
// Created by theus on 16/08/2025.
//

#include "ImChatServer.h"

#include <iostream>
#include <vector>

#include "SFML/Network/Packet.hpp"
#include "SFML/Network/TcpListener.hpp"

#if !IMCHAT_SERVER

namespace ImChat {
    namespace Server {

        std::vector<ClientInfo> clients;

        void broadcastMessage(const std::string& msg) {
            for (auto& client : clients) {
                sf::Packet packet;
                packet << msg;
                client.socket.send(packet);
            }
        }

        void runServer(unsigned short port) {
            sf::TcpListener listener;
            if (listener.listen(port) != sf::Socket::Status::Done) {
                std::cerr << "Failed to start server on port " << port << "\n";
                return;
            }

            std::cout << "Server listening on port " << port << "...\n";

            while (true) {
                sf::TcpSocket client;
                if (listener.accept(client) == sf::Socket::Status::Done) {
                    ClientInfo info;
                    info.socket = std::move(client);

                    // Receive initial username
                    sf::Packet packet;
                    if (info.socket.receive(packet) == sf::Socket::Status::Done) {
                        packet >> info.username;
                        clients.push_back(std::move(info));
                        std::cout << "User joined: " << clients.back().username << "\n";
                    }
                }


            }
        }

    }
}

#endif