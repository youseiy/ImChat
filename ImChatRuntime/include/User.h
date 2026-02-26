//
// Created by theus on 20/08/2025.
//

#ifndef IMCHAT_USER_H
#define IMCHAT_USER_H

#include "CoreTypes.h"
#include "UUID.h"

namespace ImChat {



    class User {
    public:
        User()=default;

        // Constructor
        User(Connection InConnection, UserName InUserName)
            : m_clientConnection(std::move(InConnection)), m_user_name(std::move(InUserName)) {}

        User( UserName InUserName)
            : m_user_name(std::move(InUserName)) {}



        bool operator==(const User& other) const {
            return m_user_name.username == other.m_user_name.username;
        }

        [[nodiscard]] UserName GetUserName() const;
        [[nodiscard]] std::string GetUserNameStr() const;
        [[nodiscard]] Connection& GetConnection();
        [[nodiscard]] ImChat::Status GetStatus() const;
        [[nodiscard]] ImChat::Display GetDisplay() const;
    private:

        ImChat::Display m_display;
        ImChat::Status m_status;
        ImChat::Connection m_clientConnection;
        ImChat::UserName m_user_name;
        ImChat::UUID m_internal_uuid;
    };
    using UserPtr=std::shared_ptr<User>;
}


#endif //IMCHAT_USER_H
