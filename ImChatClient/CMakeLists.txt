

# Specify include directories for glad
target_include_directories(glad PUBLIC
        dependencies/glad/include
)

# Define an executable target named "ImChatClient"
# This will compile the source file src/main.cpp into the ImChatClient executable
add_executable(ImChatClient
        src/main.cpp
        src/Window.cpp
)

# Specify include directories for ImChatClient
# PRIVATE means this include path is used only when compiling ImChatClient,
# and it won’t propagate to targets that link against ImChatClient
target_include_directories(ImChatClient
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Find the OpenGL package on the system, required for rendering
find_package(OpenGL REQUIRED)


# Link libraries and targets to ImChatClient
# PRIVATE means these dependencies are used only for ImChatClient,
# and are not propagated to targets linking ImChatClient
target_link_libraries(ImChatClient
        PRIVATE
        ImChatRuntime  # Shared runtime module handling sockets, messages, etc.
        imgui          # Dear ImGui library for GUI rendering
        SDL3::SDL3   # SDL3 library for window/input management (ensure SDL3 is properly added)
        OpenGL::GL     # OpenGL library for rendering graphics
        glad           # glad library for loading OpenGL functions
        sfml-audio
)

