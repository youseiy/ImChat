//
// Created by theus on 07/09/2025.
//

#ifndef IMCHAT_IMCHATCLIENT_H
#define IMCHAT_IMCHATCLIENT_H
#include <thread>

#include "SFML/Network/TcpSocket.hpp"

namespace ImChat {

    /*
     * @class Client
     *
     * This class connects to the chat server,
     * manages sending user messages, and runs a dedicated thread to receive incoming
     * messages asynchronously. It exposes a simplified interface for:
     *   - establishing a connection to a given host and port
     *   - sending messages to the server
     *   - registering a handler or queue for incoming messages
     *   - cleanly disconnecting and shutting down the receive thread
    */
    class Client {

    public:
        Client();

        ~Client();


        bool Login(
            const std::string& username,
            const std::string& password,
            const sf::IpAddress& serverIp,
            unsigned short port);

        void SendMessageA(const std::string &message);


        void SendMessage(const std::string& message);


        void StartListeningServer();

        void StopListeningServer();

        void listenServer();






        sf::TcpSocket& GetMutableTcpSocket();

        void Loggout();
    private:
        sf::TcpSocket m_socket;

        std::jthread m_server_listener_thread;
    };

}


#endif //IMCHAT_IMCHATCLIENT_H