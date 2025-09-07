#pragma once
#include "spdlog/spdlog.h"


namespace ImChatLog {
    template<typename... Args>
    inline void info(spdlog::format_string_t<Args...> fmt,Args&&... args) {
        spdlog::info(fmt,std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void warn(spdlog::format_string_t<Args...> fmt, Args &&...args) {
        spdlog::warn(fmt,std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void error(spdlog::format_string_t<Args...> fmt,Args&&... args) {
        spdlog::error(fmt,std::forward<Args>(args)...);
    }

}
