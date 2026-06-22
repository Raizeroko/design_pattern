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

class Ticket {
public:
    std::string assign() {
        if (status_ == "open") {
            status_ = "assigned";
            return "assigned";
        }
        return "ignored";
    }

    std::string close() {
        if (status_ == "assigned") {
            status_ = "closed";
            return "closed";
        }
        return "ignored";
    }

private:
    std::string status_ = "open";
};

} // namespace state::before
