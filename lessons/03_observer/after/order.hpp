#pragma once

#include <string>
#include <utility>
#include <vector>

namespace observer::after {

struct OrderObserver {
    virtual ~OrderObserver() = default;
    virtual void on_status_changed(const std::string& status) = 0;
};

class Order {
public:
    void subscribe(OrderObserver& observer) { observers_.push_back(&observer); }

    void ship() {
        status_ = "shipped";
        for (auto* observer : observers_) {
            observer->on_status_changed(status_);
        }
    }

private:
    std::string status_ = "created";
    std::vector<OrderObserver*> observers_;
};

class RecordingObserver final : public OrderObserver {
public:
    explicit RecordingObserver(std::string prefix) : prefix_(std::move(prefix)) {}

    void on_status_changed(const std::string& status) override {
        messages_.push_back(prefix_ + ":" + status);
    }

    const std::vector<std::string>& messages() const { return messages_; }

private:
    std::string prefix_;
    std::vector<std::string> messages_;
};

} // namespace observer::after
