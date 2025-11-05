#include "ServerMessager.h"

#include "nlohmann/json.hpp"
#include "SFML/Network/Packet.hpp"


void ServerMessenger::broadcastData(std::vector<std::shared_ptr<sf::TcpSocket>>& receivers,
                                    const std::string& data) {

    for (auto& receiver : receivers) {
        sendData(receiver, data);
    }
}

void ServerMessenger::sendData(std::shared_ptr<sf::TcpSocket>& receiver, const std::string& data) {

    sf::Packet packet;
    packet << data;
    receiver->send(packet);
}
