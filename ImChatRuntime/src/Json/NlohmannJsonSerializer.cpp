
#include <nlohmann/json.hpp>
#include "Json/NlohmannJsonSerializer.h"

using json = nlohmann::json;

std::string NlohmannJsonSerializer::serialize(const ImChat::Message &msg) const {
    json j;
    j["type"] = static_cast<int>(msg.type);
    j["sender"] = msg.sender;
    j["text"] = msg.text;
    return j.dump();
}
