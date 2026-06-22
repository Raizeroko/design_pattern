#pragma once

/*
参考重构：Observer
- OrderObserver 定义状态事件契约，Order 不再依赖短信、审计等具体接收者。
- subscribe 在运行时建立订阅关系，新增观察者无需修改 Order::ship。
- RecordingObserver 是可测试的示例接收者，保存收到的事件。
注意：Order 保存非拥有型指针，观察者生命周期必须长于订阅关系。
*/

#include <string>
#include <utility>
#include <vector>

namespace observer::after {

// 发布者和接收者之间唯一共享的事件契约。
struct OrderObserver {
    virtual ~OrderObserver() = default;
    virtual void on_status_changed(const std::string& status) = 0;
};

class Order {
public:
    void subscribe(OrderObserver& observer) { observers_.push_back(&observer); }

    void ship() {
        status_ = "shipped";
        // Order 只广播事件，不判断接收者究竟要发短信还是记审计。
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
