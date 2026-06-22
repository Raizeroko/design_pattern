/*
测试目的：锁定重构前订单发货后固定发送短信和邮件的行为。
测试步骤：调用 Order::ship，然后检查 Order 内部记录的两个通知结果及顺序。
通过含义：现有通知行为可用；但 Order 直接知道每个渠道，新增接收者必须修改它。
*/

#include "before.hpp"

#include <iostream>

int main() {
    // [发布者] 创建订单；此时它内部已经固定持有短信和邮件两个具体接收者。
    observer::before::Order order;

    // [发布动作] ship() 内部会直接点名调用 sms_.send 和 email_.send。
    order.ship();

    // [接收结果] 两个具体接收者分别处理状态，结果被 Order 收集。
    const bool ok = order.messages().size() == 2 &&
                    order.messages()[0] == "sms:shipped" &&
                    order.messages()[1] == "email:shipped";
    std::cout << (ok ? "[PASS] " : "[FAIL] ")
              << "Order should directly send both legacy notifications\n";
    return ok ? 0 : 1;
}
