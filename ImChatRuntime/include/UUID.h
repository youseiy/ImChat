#pragma once
#include "uuid_v4.h"

namespace ImChat {
    class UUID {
    public:
        UUID();

        [[nodiscard]] std::string toString() const;

        UUID(const UUID&) = default;
        UUID(UUID&&) = default;
        UUID& operator=(const UUID&) = default;
        UUID& operator=(UUID&&) = default;

        bool operator==(const UUID& other) const { return internal_uuid == other.internal_uuid; }

        bool operator!=(const UUID& other) const { return !(*this == other); }
    private:



        UUIDv4::UUID internal_uuid;
    };

}
