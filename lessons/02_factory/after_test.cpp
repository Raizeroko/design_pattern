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

