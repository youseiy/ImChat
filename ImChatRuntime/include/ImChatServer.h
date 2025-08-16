//
// Created by theus on 16/08/2025.
//

#ifndef IMCHAT_IMCHATSERVER_H
#define IMCHAT_IMCHATSERVER_H

#if !IMCHAT_SERVER
#include "SFML/Network/TcpSocket.hpp"

namespace ImChat {
    namespace Server {

        struct ClientInfo {
            sf::TcpSocket socket;
            std::string username;
        };

        void runServer(unsigned short port);
        void broadcastMessage(const std::string& msg);
    }
}

#endif

#endif //IMCHAT_IMCHATSERVER_H