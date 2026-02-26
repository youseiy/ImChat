//
// Created by theus on 20/08/2025.
//

#include "../include/User.h"



ImChat::UserName ImChat::User::GetUserName() const {
    return m_user_name;
}

std::string ImChat::User::GetUserNameStr() const {
    return m_user_name.username;
}

ImChat::Connection& ImChat::User::GetConnection() {
    return m_clientConnection;
}

ImChat::Status ImChat::User::GetStatus() const {
    return m_status;
}

ImChat::Display ImChat::User::GetDisplay() const {
    return m_display;
}
