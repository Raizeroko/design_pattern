#include "practice.hpp"

#include <iostream>
#include <memory>

int main() {
    int failures = 0;
    auto check = [&](bool passed, const char* message) {
        std::cout << (passed ? "[PASS] " : "[FAIL] ") << message << '\n';
        failures += passed ? 0 : 1;
    };

    std::unique_ptr<decorator::practice::Drink> drink =
        std::make_unique<decorator::practice::Coffee>();
    drink = std::make_unique<decorator::practice::Milk>(std::move(drink));
    drink = std::make_unique<decorator::practice::OatMilk>(std::move(drink));

    check(drink->price() == 20, "coffee + milk + oat milk should cost 20");
    check(drink->name() == "coffee+milk+oat",
          "decorators should compose the drink description");

    return failures == 0 ? 0 : 1;
}

