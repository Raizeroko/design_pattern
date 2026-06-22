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

