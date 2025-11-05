//
// Created by theus on 22/08/2025.
//

#ifndef IMCHAT_UILOGINSCREEN_H
#define IMCHAT_UILOGINSCREEN_H
#include "Client.h"
#include "UIScreen.h"


namespace ImChat {
    class UILoginScreen : public UIScreen{
    public:
        UILoginScreen()=delete;


        explicit UILoginScreen(const std::shared_ptr<Window>& InRenderWindow,const std::string& InScreenName,Client& InClient)
            : UIScreen(InRenderWindow,InScreenName,InClient){

        }

    private:
        void Render() override;

        std::string m_username{};
        std::string m_password{};

        float logged_in=false;

    };
} // ImChat

#endif //IMCHAT_UILOGINSCREEN_H