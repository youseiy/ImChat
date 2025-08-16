cmake_minimum_required(VERSION 3.15)
project(ImChat)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(dependencies/SDL3)
add_subdirectory(dependencies/imgui) # Add ImGui
add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/SFML)
add_subdirectory(ImChatRuntime)
add_subdirectory(ImChatClient)
add_subdirectory(ImChatServer)

