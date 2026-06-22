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

/*
模式角色与代码对照：
- [Subject / 发布者] Order。
- [Observer / 抽象接收者] OrderObserver。
- [ConcreteObserver / 具体接收者] RecordingObserver。
- [订阅动作] Order::subscribe。
- [发布动作] ship() 遍历 observers_ 并调用 on_status_changed。
- [接收动作] RecordingObserver::on_status_changed。
*/

namespace observer::after {

// [抽象接收者 / Observer] 发布者与所有接收者之间唯一共享的契约。
struct OrderObserver {
    virtual ~OrderObserver() = default;
    // [接收动作] Order 发布状态后，会统一调用这个方法。
    virtual void on_status_changed(const std::string& status) = 0;
};

// [发布者 / Subject] Order 只知道抽象 OrderObserver，不知道短信、邮件等具体类。
class Order {
public:
    // [订阅动作] 外部把接收者注册进发布者；Order 不负责判断它是哪种渠道。
    void subscribe(OrderObserver& observer) { observers_.push_back(&observer); }

    void ship() {
        // [领域动作] 状态变化是事件产生的原因。
        status_ = "shipped";

        // [发布动作] 遍历抽象接收者并调用统一接收动作。
        // [发布动作-对比] 这里没有 SmsNotifier、EmailNotifier 等具体类型名称。
        for (auto* observer : observers_) {
            observer->on_status_changed(status_);
        }
    }

private:
    std::string status_ = "created";
    // [订阅关系] 容器元素类型是抽象 OrderObserver*，新增渠道无需修改 Order。
    // [生命周期约束] 非拥有型指针要求观察者比订阅关系活得更久。
    std::vector<OrderObserver*> observers_;
};

// [具体接收者 / ConcreteObserver] 用 prefix 模拟 audit、risk 等下游系统。
class RecordingObserver final : public OrderObserver {
public:
    explicit RecordingObserver(std::string prefix) : prefix_(std::move(prefix)) {}

    void on_status_changed(const std::string& status) override {
        // [接收动作的实现] 接收发布者传来的状态，并执行本接收者自己的逻辑。
        messages_.push_back(prefix_ + ":" + status);
    }

    const std::vector<std::string>& messages() const { return messages_; }

private:
    // [接收者自身配置] 下游系统名称，不属于 Order。
    std::string prefix_;
    std::vector<std::string> messages_;
};

} // namespace observer::after
