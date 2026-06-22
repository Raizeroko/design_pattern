#include "before.hpp"

#include <iostream>

int main() {
    const bool accepted = adapter::before::checkout_with_legacy_sdk(100);
    const bool rejected = !adapter::before::checkout_with_legacy_sdk(0);
    std::cout << (accepted ? "[PASS] " : "[FAIL] ")
              << "legacy checkout should accept positive payment\n";
    std::cout << (rejected ? "[PASS] " : "[FAIL] ")
              << "legacy checkout should reject zero payment\n";
    return accepted && rejected ? 0 : 1;
}

