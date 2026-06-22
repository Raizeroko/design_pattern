#include "before.hpp"

#include <iostream>

int main() {
    state::before::Ticket ticket;
    const bool assigned = ticket.assign() == "assigned";
    const bool closed = ticket.close() == "closed";
    std::cout << (assigned ? "[PASS] " : "[FAIL] ")
              << "open ticket should be assigned\n";
    std::cout << (closed ? "[PASS] " : "[FAIL] ")
              << "assigned ticket should be closed\n";
    return assigned && closed ? 0 : 1;
}

