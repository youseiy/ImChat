
#pragma once
#include <map>
#include <vector>

#include "ChatThread.h"
#include "ClientTypes.h"
#include "UIScreen.h"


namespace ImChat {
    class UIChatLobby : public UIScreen{
    public:
        UIChatLobby(const std::shared_ptr<Window> &InRenderWindow, const std::string &InScreenName,Client& InClient)
            : UIScreen{InRenderWindow, InScreenName,InClient} {

            friends.emplace_back(User{UserName{std::string("test1")}});
            friends.emplace_back(User{UserName{std::string("test2")}});
        }

        void Render() override;

    private:
        void DrawChatWindows() const;

        std::vector<ImChat::ChatInstance> mOpenChats;

        // groups;

        std::vector<User> favorites;
        std::vector<User> friends;

        std::vector<std::unique_ptr<ImChat::ChatThread>> mOpens;

    };

}

