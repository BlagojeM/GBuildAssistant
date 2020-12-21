#ifndef GBA_DEBUG_HPP
#define GBA_DEBUG_HPP

#include <string_view>
#include <spdlog/spdlog.h>

namespace gba {

void die(std::string_view msg);

template <class FormatString, class ... Args>
void warn(FormatString &&fmt, Args&& ...args) {
    spdlog::warn(std::forward<FormatString>(fmt), std::forward<Args>(args)...);
}

template <class FormatString, class ... Args>
void info(FormatString &&fmt, Args&& ...args) {
    spdlog::info(std::forward<FormatString>(fmt), std::forward<Args>(args)...);
}

}

#endif
