#include "after.hpp"

#include <iostream>
#include <memory>
#include <utility>

int main() {
    std::unique_ptr<decorator::after::Drink> drink =
        std::make_unique<decorator::after::Coffee>();
    drink = std::make_unique<decorator::after::Milk>(std::move(drink));
    drink = std::make_unique<decorator::after::OatMilk>(std::move(drink));

    const bool price_ok = drink->price() == 20;
    const bool name_ok = drink->name() == "coffee+milk+oat";
    std::cout << (price_ok ? "[PASS] " : "[FAIL] ")
              << "decorators should accumulate price\n";
    std::cout << (name_ok ? "[PASS] " : "[FAIL] ")
              << "decorators should compose description\n";
    return price_ok && name_ok ? 0 : 1;
}
