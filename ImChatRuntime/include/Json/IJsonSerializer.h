#pragma once
#include <string>
#include "ImChatCoreTypes.h"

namespace  ImChat {

    class IJsonSerializer {
    public:
        virtual ~IJsonSerializer() = default;

        // Convert Message struct to string
        virtual std::string serialize(const Message& msg) const = 0;

        // Convert string to Message struct
        virtual Message deserialize(const std::string& data) const = 0;
    };
}