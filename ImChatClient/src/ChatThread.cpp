//
// Created by theus on 04/01/2026.
//

#pragma once

#include "ChatThread.h"
#include "ImChatLog.h"
#include "imgui_impl_sdl3.h"
#include "UIChatInstance.h"
#include "UILoginScreen.h"
#include "SDL3/SDL_events.h"



void ImChat::ChatThread::Start() {

    ImChatLog::info("Welcome to ImChat Client!");

    ImChat::Client client;

   window=ImChat::Window::Create(std::string{"ImChat Client2"}, 800, 600);

    window->AddUIContent<ImChat::UILoginScreen>(std::string{"LoginScreen"},client);

    Thread::Start();
}

void ImChat::ChatThread::Run() {

    while (bIsRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                bIsRunning = false;

            // Detect SDL window resize
            if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                window->SetWindowSize(event.window.data1,event.window.data2);
            }
        }
        window->BeginFrame();

        window->RenderUIContent();

        window->EndFrame();
    }
}

void ImChat::ChatThread::Stop() {
    Thread::Stop();

}
