#include "lessons/03_observer/before/order.hpp"
#include "solutions/03_observer/after/order.hpp"
#include "tests/test_framework.hpp"

void observer_tests() {
    observer::before::Order legacy;
    legacy.ship();
    EXPECT_EQ(legacy.messages().size(), 2u);

    observer::after::Order order;
    observer::after::RecordingObserver audit("audit");
    observer::after::RecordingObserver risk("risk");
    order.subscribe(audit);
    order.subscribe(risk);
    order.ship();
    EXPECT_EQ(audit.messages().front(), "audit:shipped");
    EXPECT_EQ(risk.messages().front(), "risk:shipped");
}

int main() {
    return labtest::run("observer", observer_tests);
}
