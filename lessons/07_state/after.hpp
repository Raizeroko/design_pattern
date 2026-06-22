#pragma once

/*
参考重构：State
- Ticket 把当前行为委托给 TicketState，不再维护状态字符串分支。
- OpenState、AssignedState、ClosedState 把某个状态的行为集中在同一个类。
- transition_to 显式替换状态对象，非法操作由当前状态返回 ignored。
unique_ptr 表明 Ticket 独占当前状态，迁移时旧状态自动释放。
*/

#include <memory>
#include <string>
#include <utility>

namespace state::after {

class Ticket;

// 每个状态必须明确回答所有允许的操作。
struct TicketState {
    virtual ~TicketState() = default;
    // name 用于展示当前业务状态。
    virtual std::string name() const = 0;
    // 每个状态对象都要说明领取和关闭在当前状态下如何处理。
    virtual std::string assign(Ticket& ticket) const = 0;
    virtual std::string close(Ticket& ticket) const = 0;
};

class Ticket {
public:
    // 新工单默认进入 OpenState。
    Ticket();

    // Ticket 不再判断状态，只把用户操作交给当前状态对象。
    std::string assign() { return state_->assign(*this); }
    std::string close() { return state_->close(*this); }
    std::string status() const { return state_->name(); }
    // 状态迁移集中替换当前状态对象，旧状态随 unique_ptr 自动销毁。
    void transition_to(std::unique_ptr<TicketState> state) { state_ = std::move(state); }

private:
    // 工单在任一时刻独占一个当前状态对象。
    std::unique_ptr<TicketState> state_;
};

// 已领取状态：重复领取无效，但允许关闭工单。
class AssignedState final : public TicketState {
public:
    std::string name() const override { return "assigned"; }
    std::string assign(Ticket&) const override { return "ignored"; }
    std::string close(Ticket& ticket) const override;
};

// 已关闭状态：本示例把它视为终态，所有操作都忽略。
class ClosedState final : public TicketState {
public:
    std::string name() const override { return "closed"; }
    std::string assign(Ticket&) const override { return "ignored"; }
    std::string close(Ticket&) const override { return "ignored"; }
};

// 待领取状态：允许 assign，拒绝直接 close。
class OpenState final : public TicketState {
public:
    std::string name() const override { return "open"; }
    std::string assign(Ticket& ticket) const override {
        // 状态自己决定下一状态，并要求 Ticket 完成替换。
        ticket.transition_to(std::make_unique<AssignedState>());
        return "assigned";
    }
    std::string close(Ticket&) const override { return "ignored"; }
};

// 工单创建时不再写入 "open" 字符串，而是创建 OpenState 对象。
inline Ticket::Ticket() : state_(std::make_unique<OpenState>()) {}

inline std::string AssignedState::close(Ticket& ticket) const {
    // 关闭规则集中在 AssignedState，不会散落到 Ticket::close 中。
    ticket.transition_to(std::make_unique<ClosedState>());
    return "closed";
}

} // namespace state::after
