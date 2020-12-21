#include "gba/debug.hpp"
#include <spdlog/spdlog.h>

namespace gba {
void die(std::string_view msg) {
    spdlog::error(msg);
    exit(EXIT_FAILURE);
}
}

