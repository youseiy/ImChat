//
// Created by theus on 21/08/2025.
//

#ifndef IMCHAT_USERMANAGER_H
#define IMCHAT_USERMANAGER_H

#include <functional>
#include <mutex>
#include <vector>

#include "ConnectedUsers.h"
#include "User.h"


namespace ImChat {


    class UserManager {
    public:


        UserManager(const UserManager &other) = delete;

        void operator=(const UserManager &) = delete;

        static UserManager* Get();

        ~UserManager() = default;

        std::shared_ptr<User> AddUser(std::shared_ptr<User> InUser) ;

        void RemoveUser(const User& InUser);


        /**
         * Creates a new user based on a connection
         * @param InConnection NewConnection
         * @param InUserName UserName of the Client
         */
        UserPtr createUserFromConnection(const std::shared_ptr<sf::TcpSocket> &InConnection,const std::string& InUserName);


        void ForEachUser(std::function<void(UserPtr& user)>&& predicate) {
            for (auto& user:m_users.GetVector()) {
                predicate(user);
            }
        }


        void serialize(ISerializer& s) const;
    private:
        UserManager()=default;

       static UserManager* m_instance;
        static std::mutex m_mutex;
        ConnectedUsers m_users;


    };
} // ImChat

#endif //IMCHAT_USERMANAGER_H