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

/*
概念与代码对照：
- [Context] Ticket。
- [状态表示] status_ 字符串。
- [状态判断动作] assign/close 中的 if (status_ == ...)。
- [状态迁移动作] status_ = "assigned"/"closed"。
- [问题证据] 每个操作都必须知道所有相关状态值和迁移规则。
*/

#include <string>

namespace state::before {

// [Context] Ticket 保存状态，并自己解释每个状态下允许的行为。
class Ticket {
public:
    std::string assign() {
        // [状态判断] assign 先判断当前是否为 open。
        if (status_ == "open") {
            status_ = "assigned";
            return "assigned";
        }
        // [非法操作规则] assigned/closed 状态下 assign 被忽略。
        return "ignored";
    }

    std::string close() {
        // [状态判断] close 又要判断当前是否为 assigned。
        if (status_ == "assigned") {
            status_ = "closed";
            return "closed";
        }
        return "ignored";
    }

private:
    // [状态表示 + 问题证据] status_ 是字符串，所有操作都直接依赖它。
    std::string status_ = "open";
};

} // namespace state::before
