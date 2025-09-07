//
// Created by theus on 20/08/2025.
//

#ifndef IMCHAT_USER_H
#define IMCHAT_USER_H
#include <utility>

#include "ImChatCoreTypes.h"

namespace ImChat {
    class User {
    public:

        // Constructor
        User(ClientInfo&& InClientInfo, UserName  InUserName)
            : m_clientInfo(std::move(InClientInfo)), m_user_name(std::move(InUserName)) {}

        // Delete copy constructor/assignment (cannot copy sockets)
        User(const User&) = delete;
        User& operator=(const User&) = delete;

        // Default move constructor/assignment (allow moving)
        User(User&&) noexcept = default;
        User& operator=(User&&) noexcept = default;

        // Equality operator (compare by username)
        bool operator==(const User& other) const {
            return m_user_name.username == other.m_user_name.username;
        }


        [[nodiscard]] UserName GetUserName() const;

    private:
        ClientInfo m_clientInfo;
        UserName m_user_name;
    };

}


#endif //IMCHAT_USER_H
