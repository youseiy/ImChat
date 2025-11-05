
# Create a static library target named "ImChatRuntime"
# This will be linked by the client and the server
add_library(ImChatRuntime STATIC
        src/Client.cpp
        src/Server.cpp
        src/User.cpp
        src/UserManager.cpp
        src/ServerMessager.cpp
        src/UUID.cpp
        src/IpAdress.cpp
        include/IpAdress.h
        include/MessageHelpers.h
        src/MessageHelpers.cpp
        include/MessageTypes.h
        include/Json/Serializer.h
        include/PayloadTypes.h
        include/ConnectedUsers.h
        src/ConnectedUsers.cpp
        include/pch/stdpch.h
        include/Socket/Socket.h
        include/Socket/SFMLSocket.h
        src/Socket/SFMLSocket.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

# Specify public include directories for this library
# This makes headers in 'include/' available to any target that links to ImChatRuntime
target_include_directories(ImChatRuntime
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        "../dependencies/uuid_v4")



option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

target_link_libraries(ImChatRuntime
        PUBLIC
        sfml-network
        sfml-system
        spdlog::spdlog_header_only
        nlohmann_json::nlohmann_json
)


# STD precompiled header
target_precompile_headers(ImChatRuntime PRIVATE
        include/pch/stdpch.h
)

target_link_libraries(ImChatRuntime
        INTERFACE uuid_v4
)