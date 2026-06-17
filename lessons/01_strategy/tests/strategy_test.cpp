#include "lessons/01_strategy/before/shipping.hpp"
#include "solutions/01_strategy/after/shipping.hpp"
#include "tests/test_framework.hpp"

#include <memory>

void strategy_tests() {
    EXPECT_EQ(strategy::before::shipping_fee("standard", 5, false), 20);
    strategy::after::Checkout checkout(std::make_unique<strategy::after::SameDayShipping>());
    EXPECT_EQ(checkout.shipping_fee(5, true), 45);
}

int main() {
    return labtest::run("strategy", strategy_tests);
}
