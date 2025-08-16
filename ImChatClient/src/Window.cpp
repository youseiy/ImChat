//
// Created by theus on 08/08/2025.
//

#include "Window.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl3.h"
#include "glad/glad.h"
#include "SDL3/SDL_init.h"


ImChat::ImChatClient::Window::Window(const std::string& Name,float w, float h):
    m_width(w),m_height(h)
{

    // Initialize SDL3 with video subsystem
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Error: SDL_Init failed: " << SDL_GetError() << std::endl;
        return;
    }
    // Setup OpenGL context attributes (version 3.3 Core in this example)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


    m_window = SDL_CreateWindow(
        Name.data(),
        m_width, m_height,
        SDL_WINDOW_OPENGL );

    if (!m_window) {
        std::cerr << "Error: SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    gl_context = SDL_GL_CreateContext(m_window);

    if (!gl_context) {
        std::cerr << "Error: SDL_GL_CreateContext failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return;
    }

    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize glad" << std::endl;
        SDL_GL_DestroyContext(gl_context);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return;
    }

    SDL_GL_SetSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplSDL3_InitForOpenGL(m_window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 330 core");
};


void ImChat::ImChatClient::Window::SetWindowSize(int w, int h) {
    m_width = w;
    m_height = h;
}

void ImChat::ImChatClient::Window::GetWindowSize(int &w, int &h) const {
    w = m_width;
    h = m_height;
}

void ImChat::ImChatClient::Window::BeginFrame() const{
    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void ImChat::ImChatClient::Window::EndFrame() const {
    ImGui::Render();

    int width, height;
    SDL_GetWindowSize(m_window, &width, &height);

    glViewport(0, 0, width, height);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(m_window);
}

ImChat::ImChatClient::Window::~Window()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    if (gl_context)
        SDL_GL_DestroyContext(gl_context);

    if (m_window)
        SDL_DestroyWindow(m_window);

    SDL_Quit();
}
