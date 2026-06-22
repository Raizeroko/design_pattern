#include "practice.hpp"

#include <cmath>
#include <iostream>

int main() {
    int failures = 0;
    auto check = [&](bool passed, const char* message) {
        std::cout << (passed ? "[PASS] " : "[FAIL] ") << message << '\n';
        failures += passed ? 0 : 1;
    };

    auto circle = factory::practice::ShapeFactory::create(
        factory::practice::ShapeType::circle, 2.0);
    auto square = factory::practice::ShapeFactory::create(
        factory::practice::ShapeType::square, 3.0);

    check(circle != nullptr, "factory should create a circle");
    check(square != nullptr, "factory should create a square");
    if (circle) {
        check(std::abs(circle->area() - 12.56) < 0.0001,
              "circle with radius 2 should have area 12.56");
    }
    if (square) {
        check(std::abs(square->area() - 9.0) < 0.0001,
              "square with side 3 should have area 9");
    }

    return failures == 0 ? 0 : 1;
}

