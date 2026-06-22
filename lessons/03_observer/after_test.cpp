/*
测试目的：验证订单只发布事件，多个观察者可以独立订阅并收到相同状态。
测试步骤：注册 audit 和 risk 两个观察者，发货一次，分别检查各自收到的消息。
通过含义：新增 risk 观察者不需要修改 Order::ship，发布者与接收者已经解耦。
*/

#include "after.hpp"

#include <iostream>

int main() {
    observer::after::Order order;
    observer::after::RecordingObserver audit("audit");
    observer::after::RecordingObserver risk("risk");
    order.subscribe(audit);
    order.subscribe(risk);
    order.ship();

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
