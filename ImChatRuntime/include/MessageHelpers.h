#pragma once
#include <string_view>

#include "CoreTypes.h"
#include "MessageTypes.h"


class MessageHelpers {
public:
    static std::string_view MessageTypeToString(ImChat::MessageType type) {
        switch (type) {
            case ImChat::MessageType::USER_LOGGED_IN:
                return "USER_LOGGED";
                break;
            case ImChat::MessageType::USER_UPDATE:
                return "USER_UPDATE";
                break;
            case ImChat::MessageType::CHAT_MESSAGE:
                return "CHAT_MESSAGE";
                break;
            case ImChat::MessageType::USER_LOGOUT:
                return "USER_LOGOUT";
                break;
        }
        return "";
    }
};
