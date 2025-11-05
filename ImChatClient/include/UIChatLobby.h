//
// Created by theus on 23/08/2025.
//
#pragma once
#include <map>
#include <vector>

#include "UIScreen.h"


namespace ImChat {
    class UIChatLobby : public UIScreen{
    public:
        UIChatLobby(const std::shared_ptr<Window> &InRenderWindow, const std::string &InScreenName,Client& InClient)
            : UIScreen{InRenderWindow, InScreenName,InClient} {
        }

        void Render() override;

    private:
        std::vector<std::string> m_groups;
         std::vector<std::string> m_openChats; // currently open tabs
         std::string m_activeChat;
         char m_inputBuffer[1024]{};
        std::map<std::string, char[256]> m_inputBuffers;
        std::map<std::string, std::vector<std::string>> m_chatLogs;
        std::vector<std::string> m_messages;
        std::vector<std::string> m_friends{"Alice", "Bob", "Charlie", "Diana"};

        bool m_scrollToBottom = false;
    };

}

