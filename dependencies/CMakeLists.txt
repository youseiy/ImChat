
add_subdirectory(glad)

add_subdirectory(SFML)

add_subdirectory(SDL3)

add_subdirectory(spdlog)

add_subdirectory(json)

# -------------------------------
# ImGui (submodule wrapper)
# -------------------------------

# Gather ImGui source files, including SDL3 and OpenGL3 backends
file(GLOB IMGUI_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/cpp/imgui_stdlib.cpp       # ImguiSTD
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_sdl3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

# Create static library target
add_library(imgui STATIC ${IMGUI_SOURCES})



# Include directories
target_include_directories(imgui
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui                 # ImGui root
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends       # Backend headers
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/cpp       # ImguiSTD
        ${CMAKE_CURRENT_SOURCE_DIR}/SDL3/include         # SDL3 headers
        #${CMAKE_CURRENT_SOURCE_DIR}/spdlog/include       # spdlog headers
        ${CMAKE_CURRENT_SOURCE_DIR}/json/include
)

# Link SDL3 library
target_link_libraries(imgui
        PUBLIC SDL3::SDL3
)

