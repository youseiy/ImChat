//
// Created by theus on 07/09/2025.
//

#ifndef IMCHAT_IMCHATCLIENT_H
#define IMCHAT_IMCHATCLIENT_H
#include "SFML/Network/TcpSocket.hpp"

namespace ImChat {
    class ImChatClient {


    public:
        ImChatClient();

        bool Login(
            const std::string& username,
            const std::string& password,
            const sf::IpAddress& serverIp,
            unsigned short port);


        sf::TcpSocket& GetMutableTcpSocket();
    private:
        sf::TcpSocket m_socket;

    };

}


#endif //IMCHAT_IMCHATCLIENT_H