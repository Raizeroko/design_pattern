/*
测试目的：锁定字符串状态和条件分支版本的正常迁移路径。
测试步骤：新工单先 assign，再 close，检查两个操作返回值。
通过含义：open -> assigned -> closed 主路径正确；状态行为分散的问题仍存在。
*/

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
