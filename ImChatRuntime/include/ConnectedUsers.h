#pragma once
#include <vector>
#include "User.h"
#include "Json/Serializer.h"


struct ConnectedUsers {

    std::shared_ptr<ImChat::User> add(const std::shared_ptr<ImChat::User>& NewUser);


    void serialize(ISerializer& s) const {

        for (const auto& user : m_connectedUsers) {

            s.writeArrayValue("connected_users",
                {"username",
                    user->GetUserName().username});
        };
    };


    std::vector<std::shared_ptr<ImChat::User>>& GetVector() {
        return m_connectedUsers;
    }
private:
    std::vector<std::shared_ptr<ImChat::User>> m_connectedUsers;

};


