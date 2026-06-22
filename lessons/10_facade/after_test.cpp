#include "after.hpp"

#include <iostream>

int main() {
    facade::after::CheckoutFacade checkout;
    const bool ok =
        checkout.place_order("book", 100) ==
        "reserved:book|paid|shipment:book";
    std::cout << (ok ? "[PASS] " : "[FAIL] ")
              << "facade should coordinate all checkout subsystems\n";
    return ok ? 0 : 1;
}

