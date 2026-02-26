//
// Created by theus on 23/08/2025.
//

#include "UIChatLobby.h"

#include "imgui.h"
#include "Window.h"

void ImChat::UIChatLobby::Render() {
    int w;
    int h;

    GetOwningWindow()->GetWindowSize(w,h);

    // Set fixed size and position
    ImGui::SetNextWindowSize(ImVec2(static_cast<float>(w), static_cast<float>(h)), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);


    ImGui::Begin(m_screen_name.c_str(), nullptr,
        ImGuiWindowFlags_NoDecoration);




    // Avatar do seu próprio usuário
    ImGui::Image(ImTextureRef(), ImVec2(50, 50));
    ImGui::SameLine();
    ImGui::BeginGroup();
    ImGui::TextColored(ImVec4(0.2f, 0.6f, 1.0f, 1.0f), "%s", "#Nickname");
    ImGui::Text("%s", "#Status");
    ImGui::EndGroup();

    ImGui::Separator();


    auto DrawListGroup = [this](const char* group_name,std::vector<ImChat::User>& users)
    {
        if (ImGui::TreeNode(group_name))
        {
            for (User& user : users)
            {
                ImGui::PushID(user.GetUserName().username.c_str());

                // Make the whole row clickable
                if (ImGui::Selectable("##user_row", false,
                    ImGuiSelectableFlags_Highlight,
                    ImVec2(0, 36)))
                {
                    // CLICK EVENT
                    // e.g. Open profile, select user, etc.


                }

                if (ImGui::BeginPopupContextItem("user_menu"))
                {
                    if (ImGui::MenuItem("Send Message")) {

                        //ImGui::Viewport;
                        ChatInstance instance;
                        instance.User=&user;
                        instance.ChatOpen=true;
                        mOpenChats.emplace_back(instance);

                        auto newChat = std::make_unique<ImChat::ChatThread>();
                        newChat->Start();
                        mOpens.push_back(std::move(newChat));
                    }

                    if (ImGui::MenuItem("Block"))
                        printf("Block clicked for %s\n", user.GetUserName().username.c_str());

                    ImGui::EndPopup();
                }

                ImGui::SameLine(0, 0);

                ImGui::Image(user.GetDisplay().ProfileTexture, ImVec2(30, 30));

                ImGui::SameLine();

                ImGui::TextColored(
                    user.GetStatus().Str() == "Online" ? ImVec4(0,1,0,1) : ImVec4(1,0,0,1),
                    "%s (%s)",
                    user.GetUserName().username.c_str(),
                    user.GetStatus().Str()
                );



                ImGui::PopID();
            }
            ImGui::TreePop();
        }
    };


    //DrawListGroup("Favorites", favorites);
    //DrawListGroup("Groups", groups);
    DrawListGroup("Friends", friends);

    DrawChatWindows();

ImGui::End();


}

void ImChat::UIChatLobby::DrawChatWindows() const {

    for (auto& chat: mOpenChats) {

        if (!chat.User)
            continue;

        ImGui::Begin(chat.User->GetUserNameStr().c_str());
            ImGui::TextColored(ImVec4(0,1,0,1),"Test");
        ImGui::End();

    }
}

