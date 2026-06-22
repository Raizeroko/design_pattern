#pragma once

/*
场景：订单发货后需要发送短信、邮件，并可能继续增加审计、风控等动作。
新需求：状态变化后的响应方会频繁增减。
当前问题：
1. Order 直接知道所有通知渠道，发布者依赖具体接收者。
2. 新增接收者必须修改 Order::ship，违反对修改关闭的目标。
3. 通知失败、执行顺序等逻辑会把订单类越塞越满。
练习目标：让订单只发布状态变化，让独立观察者自行响应。
*/

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
