/*
测试目的：锁定重构前调用方手工编排库存、支付和物流后的完整结果。
测试步骤：测试代码模拟调用方，亲自调用三个子系统并拼接结果。
通过含义：旧流程可以下单；问题是每个调用方都需要了解完整编排细节。
*/

#include "before.hpp"

#include <iostream>

int main() {
    // [调用方编排] 高层调用者必须知道先库存、再支付、最后物流。
    const auto stock = facade::before::reserve_stock("book");
    const auto payment = facade::before::charge(100);
    const auto shipment = facade::before::create_shipment("book");

    const bool ok =
        stock + "|" + payment + "|" + shipment ==
        "reserved:book|paid|shipment:book";
    std::cout << (ok ? "[PASS] " : "[FAIL] ")
              << "manual subsystem orchestration should place an order\n";
    return ok ? 0 : 1;
}
