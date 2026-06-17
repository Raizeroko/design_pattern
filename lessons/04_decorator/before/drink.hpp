#pragma once

#include <string>

namespace decorator::before {

inline int coffee_price(bool milk, bool syrup) {
    int price = 12;
    if (milk) {
        price += 3;
    }
    if (syrup) {
        price += 2;
    }
    return price;
}

} // namespace decorator::before
