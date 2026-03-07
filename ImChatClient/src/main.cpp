#include <functional>
#include <SDL3/SDL.h>
#include <glad/glad.h>      // Make sure glad is included before OpenGL headers
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include "Client.h"
#include "ImChatLog.h"
#include "UILoginScreen.h"
#include "Window.h"


int main(int, char**)
{
    int value = 42;

    ImChatLog::info("Welcome to ImChat Client!");

    ImChat::Client client;


    std::shared_ptr<ImChat::Window> window=ImChat::Window::Create(std::string{"ImChat Client"}, 640, 853);

    bool running = true;


    window->AddUIContent<ImChat::UILoginScreen>(std::string{"LoginScreen"},client);
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                running = false;


            if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                window->SetWindowSize(event.window.data1,event.window.data2);
            }
        }

        window->BeginFrame();

        window->RenderUIContent();

        window->EndFrame();


        /*if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            // TODO for OpenGL: restore current GL context.
        }*/
    }


    return 0;
}
