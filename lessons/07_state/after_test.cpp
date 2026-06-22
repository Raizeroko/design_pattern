/*
测试目的：同时验证合法迁移和非法操作由当前 State 决定。
测试步骤：open 拒绝 close，随后 assign；assigned 可以 close；closed 拒绝再次 assign。
通过含义：每个状态集中管理自己的行为，Ticket 不再堆叠状态条件分支。
*/

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
