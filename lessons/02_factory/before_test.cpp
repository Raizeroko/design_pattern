/*
测试目的：确认重构前具体图形本身可以正确计算面积。
测试步骤：调用方分别直接构造 Circle 和 Square，再调用统一的 area 接口。
通过含义：基础业务行为没有问题；需要改进的是调用方必须知道具体类型和构造方式。
*/

#include "before.hpp"

#include <cmath>
#include <iostream>

int main() {
    int failures = 0;
    auto check = [&](bool ok, const char* message) {
        std::cout << (ok ? "[PASS] " : "[FAIL] ") << message << '\n';
        failures += ok ? 0 : 1;
    };

    factory::before::Circle circle(2.0);
    factory::before::Square square(3.0);
    check(std::abs(circle.area() - 12.56) < 0.0001,
          "directly created circle should calculate area");
    check(std::abs(square.area() - 9.0) < 0.0001,
          "directly created square should calculate area");
    return failures == 0 ? 0 : 1;
}
