#pragma once

#include <string>

namespace state::practice {

class Ticket {
public:
    std::string assign() { return "ignored"; /* TODO */ }
    std::string close() { return "ignored"; /* TODO */ }
    std::string status() const { return "open"; /* TODO */ }
};

} // namespace state::practice

