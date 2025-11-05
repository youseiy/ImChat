//
// Created by theus on 20/08/2025.
//

#include "../include/User.h"



ImChat::UserName ImChat::User::GetUserName() const {
    return m_user_name;
}

ImChat::Connection& ImChat::User::GetConnection() {
    return m_clientConnection;
}
