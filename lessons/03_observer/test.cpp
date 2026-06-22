#include "practice.hpp"

#include <iostream>

int main() {
    int failures = 0;
    auto check = [&](bool passed, const char* message) {
        std::cout << (passed ? "[PASS] " : "[FAIL] ") << message << '\n';
        failures += passed ? 0 : 1;
    };

    observer::practice::Order order;
    observer::practice::RecordingObserver audit("audit");
    observer::practice::RecordingObserver risk("risk");
    order.subscribe(audit);
    order.subscribe(risk);
    order.ship();

    check(audit.messages().size() == 1, "audit observer should receive one event");
    check(risk.messages().size() == 1, "risk observer should receive one event");
    if (!audit.messages().empty()) {
        check(audit.messages().front() == "audit:shipped",
              "audit event should contain the new status");
    }

    return failures == 0 ? 0 : 1;
}

