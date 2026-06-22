/*
测试目的：验证 AppConfig 的共享数据行为和单实例身份。
测试步骤：先清理全局状态，写入 env，再从 instance 读取并比较两次实例地址。
通过含义：进程内入口返回同一个对象；clear_for_test 防止本测试污染其他测试。
注意：此测试不证明 set/get 的并发写安全，相关限制见 after.hpp。
*/

#include "after.hpp"

#include <iostream>

int main() {
    auto& config = singleton::after::AppConfig::instance();
    config.clear_for_test();
    config.set("env", "prod");

    const bool value_ok = config.get("env") == "prod";
    const bool identity_ok =
        &config == &singleton::after::AppConfig::instance();
    std::cout << (value_ok ? "[PASS] " : "[FAIL] ")
              << "shared config should retain values\n";
    std::cout << (identity_ok ? "[PASS] " : "[FAIL] ")
              << "instance should return the same object\n";
    return value_ok && identity_ok ? 0 : 1;
}
