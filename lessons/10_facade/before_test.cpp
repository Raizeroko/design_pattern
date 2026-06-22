/*
测试目的：锁定重构前调用方手工编排库存、支付和物流后的完整结果。
测试步骤：调用 checkout，并精确比较三个子系统按顺序拼接的输出。
通过含义：旧流程可以下单；问题是每个调用方都需要了解完整编排细节。
*/

#include "before.hpp"

#include <iostream>

int main() {
    const bool ok =
        facade::before::checkout("book", 100) ==
        "reserved:book|paid|shipment:book";
    std::cout << (ok ? "[PASS] " : "[FAIL] ")
              << "manual subsystem orchestration should place an order\n";
    return ok ? 0 : 1;
}
