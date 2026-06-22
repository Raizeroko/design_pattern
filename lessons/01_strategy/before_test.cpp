/*
测试目的：锁定重构前两种配送方式的现有计费规则。
测试输入：
1. 标准配送 5 公里、非 VIP，基础费 10 + 距离费 10。
2. 加急配送 5 公里、VIP，免基础费，只收距离费 20。
通过含义：后续重构不能悄悄改变已有客户的运费。
局限：这里只验证结果；字符串分支难扩展的问题要结合 before.hpp 阅读。
*/

#include "before.hpp"

#include <iostream>

int main() {
    int failures = 0;
    auto check = [&](bool ok, const char* message) {
        std::cout << (ok ? "[PASS] " : "[FAIL] ") << message << '\n';
        failures += ok ? 0 : 1;
    };

    check(strategy::before::shipping_fee("standard", 5, false) == 20,
          "standard shipping should cost 20");
    check(strategy::before::shipping_fee("express", 5, true) == 20,
          "VIP express shipping should waive the base fee");
    return failures == 0 ? 0 : 1;
}
