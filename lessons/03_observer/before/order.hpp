#pragma once

#include <string>
#include <vector>

namespace observer::before {

class Order {
public:
    void ship() {
        status_ = "shipped";
        messages_.push_back("sms:shipped");
        messages_.push_back("email:shipped");
    }

    const std::vector<std::string>& messages() const { return messages_; }

private:
    std::string status_ = "created";
    std::vector<std::string> messages_;
};

} // namespace observer::before
