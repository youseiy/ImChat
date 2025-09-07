//
// Created by theus on 22/08/2025.
//

#include "UILoginScreen.h"

#include "ImChatCoreTypes.h"
#include "imgui.h"
#include "imgui_stdlib.h"
#include "UIChatLobby.h"
#include "Window.h"
#include "SFML/Network/IpAddress.hpp"

namespace ImChat {
    void UILoginScreen::Render() {

        if (logged_in) return;



        int w;
        int h;

        GetOwningWindow()->GetWindowSize(w,h);

        // Set fixed size and position
        ImGui::SetNextWindowSize(ImVec2(static_cast<float>(w), static_cast<float>(h)), ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);

        ImGui::Begin("ImChat",nullptr,
             ImGuiWindowFlags_NoResize |
             ImGuiWindowFlags_NoCollapse |
             ImGuiWindowFlags_NoTitleBar |
             ImGuiWindowFlags_NoMove);

        ImGui::Dummy(ImVec2(150, 300));

        ImGui::InputText("User", &m_username);

        ImGui::InputText("Password", &m_password, ImGuiInputTextFlags_Password);

;

        if (ImGui::Button("Login")) {

            if (m_owning_client.Login(m_username,m_password,IMCHAT_SERVER_IP,IMCHAT_PORT)) {

                GetOwningWindow()->AddUIContent<UIChatLobby>(std::string{"ChatScreen"},m_owning_client);
                logged_in = true;

            }
        };

        ImGui::SameLine();

        bool bRememberLogin = false;
        ImGui::Checkbox("Remember",&bRememberLogin);

        ImGui::Spacing();

        ImGui::Button("Register");


        ImGui::End();

    }
} // ImChat