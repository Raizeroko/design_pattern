#include "practice.hpp"

#include <iostream>

int main() {
    int failures = 0;
    auto check = [&](bool passed, const char* message) {
        std::cout << (passed ? "[PASS] " : "[FAIL] ") << message << '\n';
        failures += passed ? 0 : 1;
    };

    facade::practice::CheckoutFacade checkout;
    check(checkout.place_order("book", 100) ==
              "reserved:book|paid|shipment:book",
          "facade should coordinate inventory, payment, and shipping");

    return failures == 0 ? 0 : 1;
}

