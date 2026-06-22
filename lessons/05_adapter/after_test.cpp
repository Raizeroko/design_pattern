#include "after.hpp"

#include <iostream>

int main() {
    adapter::after::LegacyPayAdapter payment;
    const bool accepted = adapter::after::checkout(payment, 100);
    const bool rejected = !adapter::after::checkout(payment, 0);
    std::cout << (accepted ? "[PASS] " : "[FAIL] ")
              << "adapter should translate OK to true\n";
    std::cout << (rejected ? "[PASS] " : "[FAIL] ")
              << "adapter should translate FAIL to false\n";
    return accepted && rejected ? 0 : 1;
}

