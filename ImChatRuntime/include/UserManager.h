//
// Created by theus on 21/08/2025.
//

#ifndef IMCHAT_USERMANAGER_H
#define IMCHAT_USERMANAGER_H

#include <mutex>
#include <vector>

#include "User.h"


namespace ImChat {


    class UserManager {
    public:
        /**
         * should not be cloneable.
         */
        UserManager(const UserManager &other) = delete;
        /**
         * should not be assignable.
         */
        void operator=(const UserManager &) = delete;

        static UserManager* Get();

        ~UserManager() = default;


        User& AddUser( User&& InUser);

        void RemoveUser(const User& InUser);




    private:
        UserManager()=default;

        static UserManager* m_instance;
        static std::mutex m_mutex;

        std::vector<User> m_users;
    };
} // ImChat

#endif //IMCHAT_USERMANAGER_H