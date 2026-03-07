//
// Created by theus on 22/08/2025.
//

#include "UILoginScreen.h"

#include "CoreTypes.h"
#include "imgui.h"
#include "imgui_stdlib.h"
#include "UIChatLobby.h"
#include "Window.h"
#include "SFML/Network/IpAddress.hpp"

namespace ImChat {
    UILoginScreen::UILoginScreen(const std::shared_ptr<Window> &InRenderWindow, const std::string &InScreenName,
        Client &InClient) : UIScreen(InRenderWindow,InScreenName,InClient)
    {
        ImGui::GetStyle().ScaleAllSizes(3);
    }

    void UILoginScreen::Render() {

       /* ImGui::ShowDemoWindow();

        return;*/

        if (logged_in) return;


        int w;
        int h;

        GetOwningWindow()->GetWindowSize(w,h);

        // Set fixed size and position
        ImGui::SetNextWindowSize(ImVec2(static_cast<float>(w), static_cast<float>(h)), ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);

        ImGui::Begin("ImChat",nullptr,
             ImGuiWindowFlags_NoDecoration);

        ImGui::Dummy(ImVec2(0, 200));

        //todo:logo
        //ImGui::Image(ImTextureRef(),ImVec2(100,100));
        ImGui::Text("Email");
        ImGui::PushID("LoginInputID");
        ImGui::InputTextWithHint("", "Email", &m_username, ImGuiInputTextFlags_None);
        ImGui::PopID();

        ImGui::Dummy(ImVec2(50,0));

        ImGui::Text("Password");
        ImGui::PushID("PasswordInputID");
        ImGui::InputTextWithHint("", "Password", &m_password, ImGuiInputTextFlags_Password);
        ImGui::PopID();

        ImGui::Dummy(ImVec2(0, 20));

        if (ImGui::Button("Login")) {

            if (m_owning_client.Login(m_username,m_password,IMCHAT_SERVER_IP,IMCHAT_PORT)) {

                GetOwningWindow()->AddUIContent<UIChatLobby>(std::string{"ChatScreen"},m_owning_client);
                logged_in = true;
            }
        };

        ImGui::SameLine(0,250);

        bool bRememberLogin = false;

        ImGui::Checkbox("Remember",&bRememberLogin);

        ImGui::Spacing();

        ImGui::Dummy(ImVec2(0, 180));

        ImGui::Text("Dont have an account?");

        ImGui::Button("Register");


        ImGui::End();

    }
} // ImChat
