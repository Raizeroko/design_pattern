/*
测试目的：锁定重构前订单发货后固定发送短信和邮件的行为。
测试步骤：调用 Order::ship，然后检查 Order 内部记录的两个通知结果及顺序。
通过含义：现有通知行为可用；但 Order 直接知道每个渠道，新增接收者必须修改它。
*/

#include "before.hpp"

#include <iostream>

int main() {
    observer::before::Order order;
    order.ship();

    const bool ok = order.messages().size() == 2 &&
                    order.messages()[0] == "sms:shipped" &&
                    order.messages()[1] == "email:shipped";
    std::cout << (ok ? "[PASS] " : "[FAIL] ")
              << "Order should directly send both legacy notifications\n";
    return ok ? 0 : 1;
}
