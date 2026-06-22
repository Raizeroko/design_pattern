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

/*
概念与代码对照：
- [发布者] Order。
- [具体接收者] SmsNotifier、EmailNotifier。
- [发布动作] Order::ship 主动调用 sms_.send、email_.send。
- [接收动作] 各 Notifier 的 send(status)。
- [问题证据] Order 字段和 ship() 都直接出现具体接收者类型/名称。
*/

namespace observer::before {

// [具体接收者] 短信渠道。它的 send() 就是“接收订单状态并执行短信通知”的动作。
class SmsNotifier {
public:
    std::string send(const std::string& status) const {
        return "sms:" + status;
    }
};

// [具体接收者] 邮件渠道。新增微信通知时还会再出现一个类似的具体类。
class EmailNotifier {
public:
    std::string send(const std::string& status) const {
        return "email:" + status;
    }
};

// [发布者] Order 是状态变化的来源；ship() 发生时需要对外发布“已发货”。
class Order {
public:
    void ship() {
        // [领域动作] 仓库发货后，订单状态从 created 变为 shipped。
        status_ = "shipped";

        // [发布动作] 发布者主动调用两个接收者的 send()，把新状态传给它们。
        messages_.push_back(sms_.send(status_));
        messages_.push_back(email_.send(status_));
        // [问题证据] Order 的成员类型直接写着 SmsNotifier 和 EmailNotifier，
        // [问题证据-续] ship() 逐个点名调用，所以 Order “知道所有通知渠道”。
        // [变化影响] 新增 WechatNotifier 必须修改成员字段和这里的发布代码。
    }

    // [测试观察点] 保存具体接收者的执行结果，便于确认通知确实发生。
    const std::vector<std::string>& messages() const { return messages_; }

private:
    // [发布者状态] Order 自己负责维护的领域数据。
    std::string status_ = "created";

    // [直接依赖] 这两个具体类型把 Order 与短信、邮件渠道绑定在一起。
    SmsNotifier sms_;
    EmailNotifier email_;

    std::vector<std::string> messages_;
};

} // namespace observer::before
