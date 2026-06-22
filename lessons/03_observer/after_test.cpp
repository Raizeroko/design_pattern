/*
测试目的：验证订单只发布事件，多个观察者可以独立订阅并收到相同状态。
测试步骤：注册 audit 和 risk 两个观察者，发货一次，分别检查各自收到的消息。
通过含义：新增 risk 观察者不需要修改 Order::ship，发布者与接收者已经解耦。
*/

#include "after.hpp"

#include <iostream>

int main() {
    // [发布者] Order 不再内置任何具体通知渠道。
    observer::after::Order order;
    // [具体接收者] audit 与 risk 都实现了统一 OrderObserver 接口。
    observer::after::RecordingObserver audit("audit");
    observer::after::RecordingObserver risk("risk");
    // [订阅动作] 接收者主动注册到发布者。
    order.subscribe(audit);
    order.subscribe(risk);
    // [发布动作] ship() 只遍历抽象 Observer 并调用统一接收动作。
    order.ship();

    // [接收结果] 每个 ConcreteObserver 独立保存自己处理的事件。
    const bool audit_ok = audit.messages().size() == 1 &&
                          audit.messages()[0] == "audit:shipped";
    const bool risk_ok = risk.messages().size() == 1 &&
                         risk.messages()[0] == "risk:shipped";
    std::cout << (audit_ok ? "[PASS] " : "[FAIL] ")
              << "audit observer should receive the event\n";
    std::cout << (risk_ok ? "[PASS] " : "[FAIL] ")
              << "new observer should work without changing Order\n";
    return audit_ok && risk_ok ? 0 : 1;
}
