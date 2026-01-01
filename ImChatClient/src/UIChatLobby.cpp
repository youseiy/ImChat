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

    // Estrutura para armazenar usuários com avatar
    struct User {
        User()=default;

        std::string name;
        ImTextureRef avatar; // a textura do avatar
        std::string status; // opcional: online/offline
    };

    // Função para desenhar um grupo de usuários
    auto DrawListGroup = [](const char* group_name, const std::vector<User>& users)
    {
        if (ImGui::TreeNode(group_name))
        {
            for (const auto& user : users)
            {
                ImGui::Image(user.avatar, ImVec2(30, 30)); // avatar do usuário
                ImGui::SameLine();

                // Clicável com Selectable
                if (ImGui::Selectable(user.name.c_str()))
                {

                }

                // Opcional: mostrar status colorido ao lado
                ImGui::SameLine();
                ImGui::TextColored(
                    user.status == "Online" ? ImVec4(0,1,0,1) : ImVec4(1,0,0,1),
                    "(%s)", user.status.c_str()
                );
            }
            ImGui::TreePop();
        }
    };

    // Exemplo de uso
    std::vector<User> favorites;

    User user;
    user.name="Matheus";
    user.status="Online";

    favorites.push_back(user);

    std::vector<User> groups;

    groups.push_back(user);

    std::vector<User> friends;

    DrawListGroup("Favorites", favorites);
    DrawListGroup("Groups", groups);
    DrawListGroup("Friends", friends);


ImGui::End();


}

