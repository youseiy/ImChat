
#include "UUID.h"

ImChat::UUID::UUID() {
    UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;

    internal_uuid= uuidGenerator.getUUID();
}

std::string ImChat::UUID::toString() const {
    return internal_uuid.str();
}

