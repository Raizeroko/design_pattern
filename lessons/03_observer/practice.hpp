#pragma once

#include <string>
#include <utility>
#include <vector>

namespace observer::practice {

struct OrderObserver {
    virtual ~OrderObserver() = default;
    virtual void on_status_changed(const std::string& status) = 0;
};

class Order {
public:
    void subscribe(OrderObserver&) { /* TODO */ }
    void ship() { /* TODO */ }
};

class RecordingObserver final : public OrderObserver {
public:
    explicit RecordingObserver(std::string prefix) : prefix_(std::move(prefix)) {}
    void on_status_changed(const std::string&) override { /* TODO */ }
    const std::vector<std::string>& messages() const { return messages_; }

private:
    std::string prefix_;
    std::vector<std::string> messages_;
};

} // namespace observer::practice

