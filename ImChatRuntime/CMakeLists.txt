
# Create a static library target named "ImChatRuntime"
# This will be linked by the client and the server
add_library(ImChatRuntime src/Socket.cpp
        src/Login.cpp
        src/ImChatServer.cpp)

# Specify public include directories for this library
# This makes headers in 'include/' available to any target that links to ImChatRuntime
target_include_directories(ImChatRuntime
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include  # Typically contains ImChatRuntime/*.h files
)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

target_link_libraries(ImChatRuntime
        PUBLIC
        sfml-network
        sfml-system
)