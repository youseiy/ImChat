#pragma once
#include <vector>
#include <memory>
#include "SFML/Network/TcpSocket.hpp"


class ServerMessenger {
public:
    static void broadcastData(std::vector<std::shared_ptr<sf::TcpSocket>>& receivers,const std::string& data);

    static void sendData(std::shared_ptr<sf::TcpSocket>& receiver, const std::string& data);

};
