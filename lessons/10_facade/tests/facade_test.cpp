#include "lessons/10_facade/after/checkout.hpp"
#include "lessons/10_facade/before/checkout.hpp"
#include "tests/test_framework.hpp"

void facade_tests() {
    EXPECT_EQ(facade::before::checkout("book", 100), "reserved:book|paid|shipment:book");
    facade::after::CheckoutFacade checkout;
    EXPECT_EQ(checkout.place_order("pen", 20), "reserved:pen|paid|shipment:pen");
}

int main() {
    return labtest::run("facade", facade_tests);
}
