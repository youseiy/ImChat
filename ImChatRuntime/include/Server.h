//
// Created by theus on 16/08/2025.
//

#ifndef IMCHAT_IMCHATSERVER_H
#define IMCHAT_IMCHATSERVER_H

#if !IMCHAT_SERVER
#include <atomic>

#include "User.h"
#include "SFML/Network/SocketSelector.hpp"
#include "SFML/Network/TcpListener.hpp"
#include "SFML/Network/TcpSocket.hpp"


namespace ImChat {

    class Server {
    public:
        Server();

        void receiveClientData();

        void runServer(unsigned short port, std::atomic<bool>& running);


    private:

        void receiveClientConnection();
        void updateClientsData();

        std::vector<User> clients;

        // Create a TCP listener to accept incoming connections
        sf::TcpListener listener;

        std::vector<std::shared_ptr<sf::TcpSocket>> ClientSockets;

        sf::SocketSelector m_selector;

    };

    /*void broadcastMessage(const std::string& msg) {
        for (auto& client : clients) {
            sf::Packet packet;
            packet << msg;

            sf::Socket::Status status=client.socket.send(packet);

        }
    }*/



}


#endif

#endif //IMCHAT_IMCHATSERVER_H