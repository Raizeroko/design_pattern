#include "lessons/04_decorator/before/drink.hpp"
#include "solutions/04_decorator/after/drink.hpp"
#include "tests/test_framework.hpp"

#include <memory>

void decorator_tests() {
    EXPECT_EQ(decorator::before::coffee_price(true, true), 17);
    std::unique_ptr<decorator::after::Drink> drink = std::make_unique<decorator::after::Coffee>();
    drink = std::make_unique<decorator::after::Milk>(std::move(drink));
    drink = std::make_unique<decorator::after::OatMilk>(std::move(drink));
    EXPECT_EQ(drink->price(), 20);
    EXPECT_EQ(drink->name(), "coffee+milk+oat");
}

int main() {
    return labtest::run("decorator", decorator_tests);
}
