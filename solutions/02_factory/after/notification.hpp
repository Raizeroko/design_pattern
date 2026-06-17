#pragma once

#include <memory>
#include <stdexcept>
#include <string>

namespace factory::after {

struct Notifier {
    virtual ~Notifier() = default;
    virtual std::string send(const std::string& message) const = 0;
};

struct EmailNotifier final : Notifier {
    std::string send(const std::string& message) const override { return "email:" + message; }
};

struct SmsNotifier final : Notifier {
    std::string send(const std::string& message) const override { return "sms:" + message; }
};

struct PushNotifier final : Notifier {
    std::string send(const std::string& message) const override { return "push:" + message; }
};

inline std::unique_ptr<Notifier> make_notifier(const std::string& channel) {
    if (channel == "email") {
        return std::make_unique<EmailNotifier>();
    }
    if (channel == "sms") {
        return std::make_unique<SmsNotifier>();
    }
    if (channel == "push") {
        return std::make_unique<PushNotifier>();
    }
    throw std::invalid_argument("unknown channel");
}

} // namespace factory::after
