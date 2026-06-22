/*
测试目的：确认重构前业务代码能够直接解释旧 SDK 的字符串返回值。
测试步骤：分别提交正金额和零金额，检查 "OK"/"FAIL" 被调用方转换后的布尔结果。
通过含义：支付行为正确；耦合点是业务代码必须理解第三方字符串协议。
*/

#include "before.hpp"

#include <iostream>

int main() {
    const bool accepted = adapter::before::checkout_with_legacy_sdk(100);
    const bool rejected = !adapter::before::checkout_with_legacy_sdk(0);
    std::cout << (accepted ? "[PASS] " : "[FAIL] ")
              << "legacy checkout should accept positive payment\n";
    std::cout << (rejected ? "[PASS] " : "[FAIL] ")
              << "legacy checkout should reject zero payment\n";
    return accepted && rejected ? 0 : 1;
}
