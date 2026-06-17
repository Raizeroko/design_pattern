#pragma once

#include <stdexcept>
#include <string>

namespace factory::before {

inline std::string send_notification(const std::string& channel, const std::string& message) {
    if (channel == "email") {
        return "email:" + message;
    }
    if (channel == "sms") {
        return "sms:" + message;
    }
    throw std::invalid_argument("unknown channel");
}

} // namespace factory::before
