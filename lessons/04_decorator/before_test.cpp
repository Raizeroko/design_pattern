#include "before.hpp"

#include <iostream>

int main() {
    const bool base_ok = decorator::before::coffee_price(false, false) == 12;
    const bool extras_ok = decorator::before::coffee_price(true, true) == 17;
    std::cout << (base_ok ? "[PASS] " : "[FAIL] ")
              << "plain coffee should cost 12\n";
    std::cout << (extras_ok ? "[PASS] " : "[FAIL] ")
              << "boolean extras should be added to the price\n";
    return base_ok && extras_ok ? 0 : 1;
}

