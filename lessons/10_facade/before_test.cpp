#include "before.hpp"

#include <iostream>

int main() {
    const bool ok =
        facade::before::checkout("book", 100) ==
        "reserved:book|paid|shipment:book";
    std::cout << (ok ? "[PASS] " : "[FAIL] ")
              << "manual subsystem orchestration should place an order\n";
    return ok ? 0 : 1;
}

