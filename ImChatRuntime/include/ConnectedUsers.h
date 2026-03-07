#pragma once
#include <vector>
#include "User.h"
#include "Json/Serializer.h"


struct ConnectedUsers {
    std::shared_ptr<ImChat::User> add(const std::shared_ptr<ImChat::User> &NewUser);


    void serialize(ISerializer &s) const {
        for (const std::shared_ptr<ImChat::User> &user: m_connectedUsers) {
            std::string username = user->GetUserNameStr();

            s.writeArrayValue("connected_users",
                              JsonField{
                                  "username",
                                  username
                              });
        };
    };


    std::vector<std::shared_ptr<ImChat::User>>& GetVector() {
        return m_connectedUsers;
    }
private:
    std::vector<std::shared_ptr<ImChat::User>> m_connectedUsers;

};


