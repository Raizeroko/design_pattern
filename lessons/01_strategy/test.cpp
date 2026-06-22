#include "practice.hpp"

#include <iostream>

int main() {
    int failures = 0;
    auto check = [&](bool passed, const char* message) {
        if (passed) {
            std::cout << "[PASS] " << message << '\n';
        } else {
            std::cerr << "[FAIL] " << message << '\n';
            ++failures;
        }
    };

    strategy::my::standard_shipping_strategy standard;
    strategy::my::shipping_context standard_checkout(&standard);
    check(standard_checkout.get_shipping_fee(5, false) == 20,
          "standard shipping: 5 km, non-VIP should cost 20");
    check(standard_checkout.get_shipping_fee(5, true) == 10,
          "standard shipping: VIP should waive the base fee");

    strategy::my::express_shipping_strategy express;
    strategy::my::shipping_context express_checkout(&express);
    check(express_checkout.get_shipping_fee(5, false) == 40,
          "express shipping: 5 km, non-VIP should cost 40");

    return failures == 0 ? 0 : 1;
}

