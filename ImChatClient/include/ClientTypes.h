#pragma once
#include <string>
#include "User.h"

namespace ImChat {

    struct ChatInstance {
        ChatInstance()=default;

        ImChat::User* User;
        bool ChatOpen = false;

    };



}
