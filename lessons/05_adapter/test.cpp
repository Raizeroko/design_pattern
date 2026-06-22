#include "practice.hpp"

#include <iostream>

int main() {
    int failures = 0;
    auto check = [&](bool passed, const char* message) {
        std::cout << (passed ? "[PASS] " : "[FAIL] ") << message << '\n';
        failures += passed ? 0 : 1;
    };

    adapter::practice::LegacyPayAdapter payment;
    check(payment.pay(100), "positive payment should be adapted to true");
    check(!payment.pay(0), "rejected payment should be adapted to false");

    return failures == 0 ? 0 : 1;
}

