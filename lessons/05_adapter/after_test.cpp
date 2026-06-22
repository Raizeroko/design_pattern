/*
测试目的：验证适配器在系统边界完成旧 SDK 到 PaymentPort 的语义转换。
测试步骤：通过统一 checkout 接口提交成功与失败两种支付。
通过含义：业务层只处理 bool 支付结果，不再认识 do_pay 或 "OK"/"FAIL"。
*/

#include "after.hpp"

#include <iostream>

int main() {
    adapter::after::LegacyPayAdapter payment;
    const bool accepted = adapter::after::checkout(payment, 100);
    const bool rejected = !adapter::after::checkout(payment, 0);
    std::cout << (accepted ? "[PASS] " : "[FAIL] ")
              << "adapter should translate OK to true\n";
    std::cout << (rejected ? "[PASS] " : "[FAIL] ")
              << "adapter should translate FAIL to false\n";
    return accepted && rejected ? 0 : 1;
}
