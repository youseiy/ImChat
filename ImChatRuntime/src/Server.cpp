//
// Created by theus on 16/08/2025.
//
#include "pch/stdpch.h"

#include "Server.h"
#include "ImChatLog.h"
#include "MessageHelpers.h"
#include "ServerMessager.h"
#include "UserManager.h"
#include "Json/JsonSerializer.h"
#include "SFML/Network/Packet.hpp"
#include "SFML/Network/TcpListener.hpp"

#if !IMCHAT_SERVER

namespace ImChat {
    Server::Server() {

        listener.setBlocking(false);
    }

    void Server::runServer(unsigned short port, std::atomic<bool>& running) {

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

    void Server::receiveClientConnection() {

        std::shared_ptr<sf::TcpSocket > IncomingSocket{std::make_shared<sf::TcpSocket>()};

        sf::Socket::Status status=listener.accept(*IncomingSocket);

        // Receive an initial packet from the client
        sf::Packet packet;
        std::string msg;
        if (IncomingSocket->receive(packet) == sf::Socket::Status::Done) {
            packet >>msg;

        }

        ImChatLog::info(" {} has connected to Server",msg);

        sf::Packet outpacket;

        //outpacket<<"Connected to server. ";


        m_selector.add(*IncomingSocket);

       UserPtr newUser{UserManager::Get()->createUserFromConnection(IncomingSocket,msg)};

        /*
         * 1. Receive new client and create connection
         * 2. Update all clients about this new client
         * 3. Update new Client with all connected clients
         *
         */

        JsonSerializer JsonS;

        NetworkMessage clientMsg;


        UserManager::Get()->serialize(JsonS);

        clientMsg.type=MessageHelpers::MessageTypeToString(ImChat::MessageType::USER_LOGGED_IN);

        clientMsg.serialize(JsonS);

        UserManager::Get()->ForEachUser([JsonS](UserPtr& user) {

            std::string raw{JsonS.str()};

            ServerMessenger::sendData(user->GetConnection().socket,raw);
        });

    }


    void Server::receiveClientData() {

        for (auto it = ClientSockets.begin(); it != ClientSockets.end(); ) {

            auto& clientSocket = *it;
            //todo:change this to JSON
            if (m_selector.isReady(*it->get())) {

                sf::Packet packet, sendPacket;

                if (clientSocket->receive(packet) == sf::Socket::Status::Done) {
                    std::cout << "Received packet with "<<packet.getDataSize()<<" bytes";
                    std::string text;
                    packet >> text;
                    sendPacket << text;
                    for (auto& client: ClientSockets) {

                        if (client!=clientSocket) {

                            sf::Socket::Status  status= client->send(packet);

                        }
                    }
                }
            }
        }
    }

    void Server::updateClientsData() {



    }
}


#endif
