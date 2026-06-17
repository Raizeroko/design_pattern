#pragma once

#include <string>

namespace state::before {

class Ticket {
public:
    std::string assign() {
        if (status_ == "open") {
            status_ = "assigned";
            return "assigned";
        }
        return "ignored";
    }

    std::string close() {
        if (status_ == "assigned") {
            status_ = "closed";
            return "closed";
        }
        return "ignored";
    }

private:
    std::string status_ = "open";
};

} // namespace state::before
