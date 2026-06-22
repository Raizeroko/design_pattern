#include "before.hpp"

#include <iostream>

int main() {
    int failures = 0;
    auto check = [&](bool ok, const char* message) {
        std::cout << (ok ? "[PASS] " : "[FAIL] ") << message << '\n';
        failures += ok ? 0 : 1;
    };

    check(strategy::before::shipping_fee("standard", 5, false) == 20,
          "standard shipping should cost 20");
    check(strategy::before::shipping_fee("express", 5, true) == 20,
          "VIP express shipping should waive the base fee");
    return failures == 0 ? 0 : 1;
}

