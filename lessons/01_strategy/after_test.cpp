/*
测试目的：验证 Strategy 重构既保持旧算法，又能独立增加新算法。
测试步骤：
1. 把 StandardShipping 注入 Checkout，确认原标准配送仍为 20。
2. 换成 SameDayShipping，确认 Checkout 无需修改即可计算新价格 45。
通过含义：Checkout 只负责使用策略，算法变化已经从结账流程中分离。
*/

#include "after.hpp"

#include <iostream>
#include <memory>

int main() {
    int failures = 0;
    auto check = [&](bool ok, const char* message) {
        std::cout << (ok ? "[PASS] " : "[FAIL] ") << message << '\n';
        failures += ok ? 0 : 1;
    };

    strategy::after::Checkout standard(
        std::make_unique<strategy::after::StandardShipping>());
    check(standard.shipping_fee(5, false) == 20,
          "strategy should preserve standard shipping");

    strategy::after::Checkout same_day(
        std::make_unique<strategy::after::SameDayShipping>());
    check(same_day.shipping_fee(5, true) == 45,
          "new same-day strategy should work without changing Checkout");
    return failures == 0 ? 0 : 1;
}
