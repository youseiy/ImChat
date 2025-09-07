#pragma once
#include <string>

#include "UIScreen.h"
#include "SDL3/SDL_video.h"


namespace ImChat {
    class Window : public std::enable_shared_from_this<Window> {
    public:
        static std::shared_ptr<Window> Create(const std::string& name, float w, float h) {
            return std::shared_ptr<Window>(new Window(name, w, h));
        }

        // Delete copy and move semantics to prevent copying the SDL_Window*
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;
        Window()=delete;

        void SetWindowSize(int w, int h);
        void GetWindowSize(int& w, int& h) const;

        void BeginFrame();
        void RenderUIContent();
        void EndFrame();

        ~Window();

        template<typename TUIScreen, typename... Args>
        void AddUIContent(Args&&... args);

    private:
        Window(const std::string& Name,float w, float h);

        std::unique_ptr<UIScreen> m_rootScreen;

        SDL_Window* m_window{nullptr};
        SDL_GLContext gl_context{nullptr};

        float m_width;
        float m_height;
    };

    template<typename TUIScreen, typename... Args>
    void Window::AddUIContent(Args&&... args) {
        m_rootScreen = std::make_unique<TUIScreen>(shared_from_this(), std::forward<Args>(args)...);
    }

}
