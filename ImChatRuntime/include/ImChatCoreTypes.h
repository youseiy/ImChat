//
// Created by theus on 20/08/2025.
//

#ifndef IMCHAT_IMCHATCORETYPES_H
#define IMCHAT_IMCHATCORETYPES_H
#include <cstdint>
#include <string>
#include <unordered_set>
#include <vector>

#include "SFML/Network/IpAddress.hpp"
#include "SFML/Network/TcpSocket.hpp"

namespace ImChat {

    //Socket port
    inline constexpr unsigned short IMCHAT_PORT = 5000;
    //Ip - default local host
    inline const sf::IpAddress IMCHAT_SERVER_IP{127,0,0,1};

    struct ClientInfo {

        // Delete copy constructor and copy assignment
        ClientInfo(const ClientInfo&) = delete;
        ClientInfo& operator=(const ClientInfo&) = delete;

        // Default move constructor and move assignment
        ClientInfo(ClientInfo&&) noexcept = default;
        ClientInfo& operator=(ClientInfo&&) noexcept = default;

        // Default constructor
        ClientInfo() = default;


        sf::TcpSocket socket;
    };

    struct UserID {

        std::uint64_t id;


        bool operator==(const UserID& other) const
        {
            return this->id == other.id;
        }

        struct HashFunction
        {
            size_t operator()(const UserID& userid) const
            {
                return std::hash<int>()(userid.id);;
            }
        };
    };

    struct UserName {

        bool operator==(const UserName& other) const {
            return username == other.username;
        }

        std::string username;
    };

    struct Friend {
        std::uint64_t id;
    };


    struct Password {
        Password()=delete;

        std::string password;

    };

    struct ChatID {
        ChatID()=delete;
    };


    struct Message {
        Message()=default;
    };


    struct Chat {
        Chat()=delete;

        std::uint64_t id;

        std::vector<Message> m_messages;

        std::unordered_set<UserID> m_members;

        bool m_is_group{false};

        struct HashFunction
        {
            size_t operator()(const Chat& chat) const
            {
                return std::hash<int>()(chat.id);;
            }
        };
    };
}


#endif //IMCHAT_IMCHATCORETYPES_H