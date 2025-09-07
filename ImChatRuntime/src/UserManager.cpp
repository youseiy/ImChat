//
// Created by theus on 21/08/2025.
//
#include "UserManager.h"




namespace ImChat {
    // Define static members
    std::mutex UserManager::m_mutex;
    UserManager* UserManager::m_instance{nullptr};

    UserManager * UserManager::Get() {
        if (m_instance == nullptr) // first check without lock
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_instance == nullptr) // second check with lock
            {
                m_instance = new UserManager;
            }
        return m_instance;
    }

    User& UserManager::AddUser(User&& InUser) {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_users.emplace_back(std::move(InUser));
    }

    void UserManager::RemoveUser(const User& InUser) {
        std::lock_guard<std::mutex> lock(m_mutex);

        std::erase_if(
            m_users,
            [&InUser](const User& user) { return user.GetUserName() == InUser.GetUserName(); }
        );
    }

} // ImChat