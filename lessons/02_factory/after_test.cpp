/*
测试目的：验证调用方可以通过工厂创建对象，而不直接构造具体图形。
测试步骤：向 ShapeFactory 提供强类型 ShapeType 和尺寸，再通过 Shape 接口计算面积。
通过含义：创建规则集中在工厂中，使用图形的代码不再承担构造职责。
*/

#include "after.hpp"

#include <cmath>
#include <iostream>

int main() {
    int failures = 0;
    auto check = [&](bool ok, const char* message) {
        std::cout << (ok ? "[PASS] " : "[FAIL] ") << message << '\n';
        failures += ok ? 0 : 1;
    };

    auto circle = factory::after::ShapeFactory::create(
        factory::after::ShapeType::circle, 2.0);
    auto square = factory::after::ShapeFactory::create(
        factory::after::ShapeType::square, 3.0);
    check(circle && std::abs(circle->area() - 12.56) < 0.0001,
          "factory should create the requested circle");
    check(square && std::abs(square->area() - 9.0) < 0.0001,
          "factory should create the requested square");
    return failures == 0 ? 0 : 1;
}
