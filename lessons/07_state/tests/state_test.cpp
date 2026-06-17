#include "lessons/07_state/after/ticket.hpp"
#include "lessons/07_state/before/ticket.hpp"
#include "tests/test_framework.hpp"

void state_tests() {
    state::before::Ticket legacy;
    EXPECT_EQ(legacy.assign(), "assigned");
    EXPECT_EQ(legacy.close(), "closed");

    state::after::Ticket ticket;
    EXPECT_EQ(ticket.close(), "ignored");
    EXPECT_EQ(ticket.assign(), "assigned");
    EXPECT_EQ(ticket.status(), "assigned");
    EXPECT_EQ(ticket.close(), "closed");
    EXPECT_EQ(ticket.assign(), "ignored");
}

int main() {
    return labtest::run("state", state_tests);
}
