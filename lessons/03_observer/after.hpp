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
    // status 是订单发布的事件数据，观察者自行决定如何响应。
    virtual void on_status_changed(const std::string& status) = 0;
};

// Order 现在只管理状态和订阅者列表，不知道任何具体通知渠道。
class Order {
public:
    // 外部在组装业务流程时注册短信、审计或风控观察者。
    void subscribe(OrderObserver& observer) { observers_.push_back(&observer); }

    void ship() {
        // 领域状态仍由 Order 自己维护。
        status_ = "shipped";
        // Order 只广播事件，不判断接收者究竟要发短信还是记审计。
        for (auto* observer : observers_) {
            observer->on_status_changed(status_);
        }
    }

private:
    std::string status_ = "created";
    // 非拥有型指针：Order 不销毁观察者，调用方必须保证其生命周期。
    std::vector<OrderObserver*> observers_;
};

// 可记录事件的示例观察者；prefix 可代表 audit、risk 等下游系统。
class RecordingObserver final : public OrderObserver {
public:
    explicit RecordingObserver(std::string prefix) : prefix_(std::move(prefix)) {}

    void on_status_changed(const std::string& status) override {
        // 每个观察者在自己的类里处理事件，不再修改 Order。
        messages_.push_back(prefix_ + ":" + status);
    }

    const std::vector<std::string>& messages() const { return messages_; }

private:
    // 下游系统名称，用于展示同一事件被不同接收方独立处理。
    std::string prefix_;
    std::vector<std::string> messages_;
};

} // namespace observer::after
