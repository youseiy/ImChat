

#include "ConnectedUsers.h"


std::shared_ptr<ImChat::User> ConnectedUsers::add(const std::shared_ptr<ImChat::User>& NewUser) {
    return m_connectedUsers.emplace_back(NewUser);
}