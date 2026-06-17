#include "lessons/05_adapter/before/payment.hpp"
#include "solutions/05_adapter/after/payment.hpp"
#include "tests/test_framework.hpp"

void adapter_tests() {
    EXPECT_TRUE(adapter::before::checkout_with_legacy_sdk(100));
    adapter::after::LegacyPayAdapter payment;
    EXPECT_TRUE(adapter::after::checkout(payment, 100));
    EXPECT_TRUE(!adapter::after::checkout(payment, 0));
}

int main() {
    return labtest::run("adapter", adapter_tests);
}
