option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)


# Define an executable target named "ImChatServer"
# This compiles src/main.cpp into the server executable
add_executable(ImChatServer
        src/main.cpp
)

# Add include directories used when compiling ImChatServer
# PRIVATE means the include path is only needed when compiling this target
target_include_directories(ImChatServer
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include  # Allows includes like "ImChatServer/SomeHeader.h"
)


# Link the ImChatRuntime static library to this server target
# This gives access to socket abstraction, message types, etc.
target_link_libraries(ImChatServer
        PRIVATE
        ImChatRuntime
)