#pragma once
#include <cstdint>
#include <string>
#include "Json/Serializer.h"

namespace ImChat {

    enum class MessageType : std::uint8_t {
        USER_LOGGED_IN,
        USER_UPDATE,
        CHAT_MESSAGE,
        USER_LOGOUT,
    };


    struct NetworkMessage {
        std::string type;
        std::string payload;


        void serialize(ISerializer& s) const {
            s.write("type",type);
        };
    };

    struct ChatMessage {
        std::string sender;
        std::string text;
        std::string timestamp;

        void serialize(ISerializer& s) const {
            s.write("sender",sender);
            s.write("text",text);
            s.write("timestamp",timestamp);
        };
    };

}

