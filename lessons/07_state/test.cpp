#include "practice.hpp"

#include <iostream>

int main() {
    int failures = 0;
    auto check = [&](bool passed, const char* message) {
        std::cout << (passed ? "[PASS] " : "[FAIL] ") << message << '\n';
        failures += passed ? 0 : 1;
    };

    state::practice::Ticket ticket;
    check(ticket.close() == "ignored", "open ticket cannot be closed directly");
    check(ticket.assign() == "assigned", "open ticket can be assigned");
    check(ticket.status() == "assigned", "assign should change the state");
    check(ticket.close() == "closed", "assigned ticket can be closed");
    check(ticket.assign() == "ignored", "closed ticket cannot be assigned");

    return failures == 0 ? 0 : 1;
}

