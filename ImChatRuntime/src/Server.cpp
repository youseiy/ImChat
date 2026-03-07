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
namespace {
    std::string TrimAtFirstNull(const std::string& value) {
        const auto nullPos = value.find('\0');
        if (nullPos == std::string::npos) {
            return value;
        }
        return value.substr(0, nullPos);
    }
}

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
        if (status != sf::Socket::Status::Done) {
            return;
        }

        // Receive an initial packet from the client
        sf::Packet packet;
        std::string msg;
        if (IncomingSocket->receive(packet) == sf::Socket::Status::Done) {
            packet >>msg;
            msg = TrimAtFirstNull(msg);
        } else {
            ImChatLog::warn("Client connected but did not send username packet");
            return;

        }

        ImChatLog::info(" {} has connected to Server",msg);

        m_selector.add(*IncomingSocket);
        ClientSockets.emplace_back(IncomingSocket);

        // Send all currently connected users to the new client (before adding it).
        JsonSerializer currentUsersSerializer;
        currentUsersSerializer.write(
            "type",
            std::string(MessageHelpers::MessageTypeToString(ImChat::MessageType::USER_UPDATE))
        );
        UserManager::Get()->serialize(currentUsersSerializer);

        const std::string currentUsersRaw{currentUsersSerializer.str()};
        ServerMessenger::sendData(IncomingSocket, currentUsersRaw);
        ImChatLog::info(
            "Sent connected users snapshot to {}:\n{}",
            msg,
            currentUsersSerializer.prettyStr(2)
        );

        // Add the new user and notify everyone else about this single user.
        UserPtr newUser{UserManager::Get()->createUserFromConnection(IncomingSocket, msg)};
        JsonSerializer newUserSerializer;

        newUserSerializer.writeArrayValue(
            "connected_users",
            JsonField{"username", newUser->GetUserNameStr()}
        );

        newUserSerializer.write(
            "type",
            std::string(MessageHelpers::MessageTypeToString(ImChat::MessageType::USER_LOGGED_IN))
        );

        const std::string newUserRaw{newUserSerializer.str()};

        UserManager::Get()->ForEachUser([&newUser, &newUserRaw](UserPtr& user) {
            if (user == newUser) {
                return;
            }
            ServerMessenger::sendData(user->GetConnection().socket, newUserRaw);
        });
        ImChatLog::info("Broadcasted new connected user:\n{}", newUserSerializer.prettyStr(2));

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
