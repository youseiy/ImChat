#pragma once
#include <string>

#include "UIScreen.h"
#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_video.h"


namespace ImChat {
    class Window : public std::enable_shared_from_this<Window> {
    public:
        static std::shared_ptr<Window> Create(const std::string& name, float w, float h) {
            return std::shared_ptr<Window>(new Window(name, w, h));
        }


        // Enable move
        Window(Window&& other) noexcept
            : m_rootScreen(std::move(other.m_rootScreen)),
              m_window(other.m_window),
              gl_context(other.gl_context),
              m_width(other.m_width),
              m_height(other.m_height)
        {
            other.m_window = nullptr;
            other.gl_context = nullptr;
            other.m_width = 0;
            other.m_height = 0;


        }

        Window& operator=(Window&& other) noexcept {
            if (this != &other) {
                m_rootScreen = std::move(other.m_rootScreen);

                // Clean up current SDL resources if exist
                if (m_window) SDL_DestroyWindow(m_window);
                if (gl_context) SDL_GL_DestroyContext(gl_context);

                m_window = other.m_window;
                gl_context = other.gl_context;
                m_width = other.m_width;
                m_height = other.m_height;

                other.m_window = nullptr;
                other.gl_context = nullptr;
                other.m_width = 0;
                other.m_height = 0;
            }
            return *this;
        }

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
        std::unique_ptr<UIScreen> m_pendingScreen;
        bool m_isRenderingUI{false};

        SDL_Window* m_window{nullptr};
        SDL_GLContext gl_context{nullptr};

        float m_width;
        float m_height;
    };



    template<typename TUIScreen, typename... Args>
    void Window::AddUIContent(Args&&... args) {
        auto nextScreen = std::make_unique<TUIScreen>(shared_from_this(), std::forward<Args>(args)...);
        if (m_isRenderingUI) {
            m_pendingScreen = std::move(nextScreen);
            return;
        }
        m_rootScreen = std::move(nextScreen);
    }

}
