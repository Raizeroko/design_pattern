#include "after.hpp"

#include <iostream>

int main() {
    state::after::Ticket ticket;
    const bool invalid_close = ticket.close() == "ignored";
    const bool assigned = ticket.assign() == "assigned" &&
                          ticket.status() == "assigned";
    const bool closed = ticket.close() == "closed" &&
                        ticket.status() == "closed";
    const bool closed_is_final = ticket.assign() == "ignored";

    std::cout << (invalid_close ? "[PASS] " : "[FAIL] ")
              << "open state should reject close\n";
    std::cout << (assigned ? "[PASS] " : "[FAIL] ")
              << "open state should transition to assigned\n";
    std::cout << (closed && closed_is_final ? "[PASS] " : "[FAIL] ")
              << "assigned should close and closed should reject assign\n";
    return invalid_close && assigned && closed && closed_is_final ? 0 : 1;
}

