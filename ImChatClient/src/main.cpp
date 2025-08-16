#include <SDL3/SDL.h>
#include <glad/glad.h>      // Make sure glad is included before OpenGL headers
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>

#include "Login.h"
#include "Window.h"

int main(int, char**)
{
    ImChat::ImChatClient::Window window{"ImChat Client", 800, 600};

    bool running = true;

    bool show_demo_window = false;


    char username[128] = "";
    char password[128] = "";
    bool logged_in = false;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                running = false;

            // Detect SDL window resize
            if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                window.SetWindowSize(event.window.data1,event.window.data2);
            }
        }
        window.BeginFrame();

        // Show ImGui demo window (you can replace this with your own UI)
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);


        int w;
        int h;

        window.GetWindowSize(w,h);

        // Set fixed size and position
        ImGui::SetNextWindowSize(ImVec2(static_cast<float>(w), static_cast<float>(h)), ImGuiCond_Always);
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);



        ImGui::Begin("ImChat",nullptr,
             ImGuiWindowFlags_NoResize |
             ImGuiWindowFlags_NoCollapse |
             ImGuiWindowFlags_NoTitleBar |
             ImGuiWindowFlags_NoMove);

        ImGui::Dummy(ImVec2(150, 300));

        ImGui::InputText("User", username, IM_ARRAYSIZE(username));

        ImGui::InputText("Password", password, IM_ARRAYSIZE(password), ImGuiInputTextFlags_Password);

        if (ImGui::Button("Login")) {

            if (ImChat::tryLogin(username,password,sf::IpAddress::resolve("127.0.0.1").value(),5000)) {
                logged_in = true;
            }
        };

        ImGui::SameLine();

        bool bRememberLogin = false;
        ImGui::Checkbox("Remember",&bRememberLogin);

        ImGui::Spacing();


        ImGui::Button("Register");





        ImGui::End();

        window.EndFrame();
    }

    return 0;
}
