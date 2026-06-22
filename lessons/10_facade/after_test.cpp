/*
测试目的：验证 Facade 用一个高层接口完成与旧流程相同的下单编排。
测试步骤：调用 place_order，只提供商品和金额，再检查完整业务结果。
通过含义：调用方不再直接认识三个子系统，编排知识集中在 CheckoutFacade。
*/

#include "after.hpp"

#include <iostream>

int main() {
    facade::after::CheckoutFacade checkout;
    const bool ok =
        checkout.place_order("book", 100) ==
        "reserved:book|paid|shipment:book";
    std::cout << (ok ? "[PASS] " : "[FAIL] ")
              << "facade should coordinate all checkout subsystems\n";
    return ok ? 0 : 1;
}
