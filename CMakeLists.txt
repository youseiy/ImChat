cmake_minimum_required(VERSION 3.15)
project(ImChat)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(dependencies)
add_subdirectory(ImChatRuntime)
add_subdirectory(ImChatClient)
add_subdirectory(ImChatServer)

