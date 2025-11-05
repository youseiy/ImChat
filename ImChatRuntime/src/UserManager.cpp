//
// Created by theus on 21/08/2025.
//
#include "UserManager.h"
#include "ImChatLog.h"


namespace ImChat {
    std::mutex UserManager::m_mutex;
    UserManager* UserManager::m_instance{nullptr};


    UserManager * UserManager::Get() {

        std::lock_guard<std::mutex> lock(m_mutex);

        if (m_instance == nullptr)
        {
            m_instance = new UserManager;
        }
        return m_instance;

    }

    std::shared_ptr<User> UserManager::AddUser(std::shared_ptr<User> InUser) {

        std::lock_guard<std::mutex> lock(m_mutex);
        return m_users.add(InUser);
    }

    void UserManager::RemoveUser(const User& InUser) {
        std::lock_guard<std::mutex> lock(m_mutex);

    }

        UserPtr UserManager::createUserFromConnection(const std::shared_ptr<sf::TcpSocket> &InConnection, const std::string& InUserName) {

            ImChatLog::info("Created new user {} for connection",InUserName);

            Connection newConnection{InConnection};

            UserName userName{InUserName};

            auto newUser{ std::make_shared<User>(std::move(newConnection),std::move(userName))};

            return AddUser(newUser);
        }

        void UserManager::serialize(ISerializer &s) const {

            return m_users.serialize(s);
        }
};
