#include "after.hpp"

#include <iostream>

int main() {
    observer::after::Order order;
    observer::after::RecordingObserver audit("audit");
    observer::after::RecordingObserver risk("risk");
    order.subscribe(audit);
    order.subscribe(risk);
    order.ship();

    const bool audit_ok = audit.messages().size() == 1 &&
                          audit.messages()[0] == "audit:shipped";
    const bool risk_ok = risk.messages().size() == 1 &&
                         risk.messages()[0] == "risk:shipped";
    std::cout << (audit_ok ? "[PASS] " : "[FAIL] ")
              << "audit observer should receive the event\n";
    std::cout << (risk_ok ? "[PASS] " : "[FAIL] ")
              << "new observer should work without changing Order\n";
    return audit_ok && risk_ok ? 0 : 1;
}

