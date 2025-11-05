#pragma once

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

    struct Connection {

        Connection(const Connection&) = delete;

        Connection() = default;

        explicit Connection(const std::shared_ptr<sf::TcpSocket>& in_connection)
        {
            socket=in_connection;
        }

        Connection& operator=(const Connection&) = delete;

        Connection(Connection&&) noexcept = default;
        Connection& operator=(Connection&&) noexcept = default;

        std::shared_ptr<sf::TcpSocket> socket;
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





    struct Chat {
        Chat()=delete;

        std::uint64_t id;

        //std::vector<Message> m_messages;

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

