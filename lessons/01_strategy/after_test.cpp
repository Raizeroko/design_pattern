#include "after.hpp"

#include <iostream>
#include <memory>

int main() {
    int failures = 0;
    auto check = [&](bool ok, const char* message) {
        std::cout << (ok ? "[PASS] " : "[FAIL] ") << message << '\n';
        failures += ok ? 0 : 1;
    };

    strategy::after::Checkout standard(
        std::make_unique<strategy::after::StandardShipping>());
    check(standard.shipping_fee(5, false) == 20,
          "strategy should preserve standard shipping");

    strategy::after::Checkout same_day(
        std::make_unique<strategy::after::SameDayShipping>());
    check(same_day.shipping_fee(5, true) == 45,
          "new same-day strategy should work without changing Checkout");
    return failures == 0 ? 0 : 1;
}

