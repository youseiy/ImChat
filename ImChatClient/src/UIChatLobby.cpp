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
    ImGuiWindowFlags_MenuBar |
    ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoCollapse |
    ImGuiWindowFlags_NoTitleBar |
    ImGuiWindowFlags_NoMove);

// Split into two columns: chat + friends
ImGui::Columns(2, nullptr, true);

// ---- Left: Chat Tabs ----
if (!m_openChats.empty() && ImGui::BeginTabBar("ChatTabs", ImGuiTabBarFlags_Reorderable)) {
    for (size_t i = 0; i < m_openChats.size(); ++i) {
        std::string& friendName = m_openChats[i];

        ImGuiTabItemFlags tab_flags = ImGuiTabItemFlags_None;

        bool open = true;
        if (friendName == m_activeChat) {
            tab_flags |= ImGuiTabItemFlags_SetSelected;
        }

        if (ImGui::BeginTabItem(friendName.c_str(), &open, tab_flags)) {
            m_activeChat = friendName;

            // Chat history
            ImGui::BeginChild("ChatHistory", ImVec2(0, -80), true, ImGuiWindowFlags_HorizontalScrollbar);
            auto& chatMessages = m_chatLogs[friendName];
            for (const auto& msg : chatMessages) {
                ImGui::TextWrapped("%s", msg.c_str());
            }
            if (m_scrollToBottom) {
                ImGui::SetScrollHereY(1.0f);
                m_scrollToBottom = false;
            }
            ImGui::EndChild();

            // Input
            ImGui::PushItemWidth(-100);
            ImGui::InputTextMultiline("##ChatInput", m_inputBuffer, IM_ARRAYSIZE(m_inputBuffer),
                                      ImVec2(0, 70),
                                      ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CtrlEnterForNewLine | ImGuiInputTextFlags_EnterReturnsTrue);
            ImGui::PopItemWidth();

            ImGui::SameLine();
            if (ImGui::Button("Send", ImVec2(90, 70))) {
                if (strlen(m_inputBuffer) > 0) {
                    chatMessages.push_back("You: " + std::string(m_inputBuffer));
                    m_inputBuffer[0] = '\0';
                    m_scrollToBottom = true;
                }
            }

            ImGui::EndTabItem();
        }

        // If tab closed
        if (!open) {
            if (m_activeChat == friendName) m_activeChat.clear();
            m_openChats.erase(m_openChats.begin() + i);
            --i;
        }
    }
    ImGui::EndTabBar();
}

// ---- Right: Friends list ----
ImGui::NextColumn();
ImGui::BeginChild("FriendsList", ImVec2(0, 0), true);
ImGui::Text("Friends");
ImGui::Separator();


    // Show your own username at the top
    ImGui::TextDisabled("Yousei");
    ImGui::Separator();


    for (auto& friendName : m_friends) {
        bool isSelected = (m_activeChat == friendName);
        if (ImGui::Selectable(friendName.c_str(), isSelected)) {
            // Only add a new tab if it isn’t already open
            if (std::ranges::find(m_openChats.begin(), m_openChats.end(), friendName) == m_openChats.end()) {
                m_openChats.push_back(friendName); // friendName must be std::string
            }
            m_activeChat = friendName; // Switch to this chat
        }
    }

    // Groups section
    ImGui::Separator();
    ImGui::Text("Groups");
    ImGui::Separator();

    for (auto& groupName : m_groups) { // assuming m_groups is std::vector<std::string>
        bool isSelected = (m_activeChat == groupName);
        if (ImGui::Selectable(groupName.c_str(), isSelected)) {
            // Only add a new tab if it isn’t already open
            if (std::ranges::find(m_openChats.begin(), m_openChats.end(), groupName) == m_openChats.end()) {
                m_openChats.push_back(groupName);
            }
            m_activeChat = groupName;
        }
    }

ImGui::EndChild();

ImGui::Columns(1);
ImGui::End();


}

