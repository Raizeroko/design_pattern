#pragma once

/*
场景：工单从 open 进入 assigned，再进入 closed；不同状态允许的操作不同。
新需求：未来会增加 reopened、cancelled 等状态和迁移规则。
当前问题：
1. 每个操作都包含状态分支，状态越多，分支呈乘法增长。
2. 某个状态的行为分散在多个成员函数中，难以整体理解。
3. 非法迁移靠重复判断维护，容易遗漏。
练习目标：让当前状态对象决定行为，并显式表达状态迁移。
*/

#include <string>

namespace state::before {

// Ticket 同时保存状态字符串，并在每个操作中解释这个字符串。
class Ticket {
public:
    std::string assign() {
        // 只有 open 工单允许被客服领取。
        if (status_ == "open") {
            status_ = "assigned";
            return "assigned";
        }
        // assigned 或 closed 时调用 assign 都被忽略。
        return "ignored";
    }

    std::string close() {
        // 只有已经 assigned 的工单允许关闭。
        if (status_ == "assigned") {
            status_ = "closed";
            return "closed";
        }
        return "ignored";
    }

private:
    // 字符串状态允许任意值，且所有操作都要重复比较它。
    std::string status_ = "open";
};

} // namespace state::before
