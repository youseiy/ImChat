#pragma once
#include <string>

#include "SDL3/SDL_video.h"


namespace ImChat::ImChatClient {

    class Window {
    public:
        Window(const std::string& Name,float w, float h);

        // Delete copy and move semantics to prevent copying the SDL_Window*
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;
        Window()=delete;

        void SetWindowSize(int w, int h);
        void GetWindowSize(int& w, int& h) const;

        void BeginFrame() const;
        void EndFrame() const;

        ~Window();

    private:
        SDL_Window* m_window;
        SDL_GLContext gl_context;

        float m_width;
        float m_height;

    };




}
