#include "before.hpp"

#include <iostream>

int main() {
    observer::before::Order order;
    order.ship();

    const bool ok = order.messages().size() == 2 &&
                    order.messages()[0] == "sms:shipped" &&
                    order.messages()[1] == "email:shipped";
    std::cout << (ok ? "[PASS] " : "[FAIL] ")
              << "Order should directly send both legacy notifications\n";
    return ok ? 0 : 1;
}

