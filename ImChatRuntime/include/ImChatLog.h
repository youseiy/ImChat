#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace ImChatLog {

    // Connection log
    inline std::shared_ptr<spdlog::logger> connection_logger = spdlog::stdout_color_mt({"Connection"}, spdlog::color_mode::always);

    namespace Connection {

        template<typename... Args>
        inline void info(spdlog::format_string_t<Args...> fmt, Args&&... args) {
            connection_logger->info(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        inline void warn(spdlog::format_string_t<Args...> fmt, Args&&... args) {
            connection_logger->warn(fmt, std::forward<Args>(args)...);
        }

        template<typename... Args>
        inline void error(spdlog::format_string_t<Args...> fmt, Args&&... args) {
            connection_logger->error(fmt, std::forward<Args>(args)...);
        }

    } // namespace Connection

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
