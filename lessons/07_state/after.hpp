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
    virtual std::string name() const = 0;
    virtual std::string assign(Ticket& ticket) const = 0;
    virtual std::string close(Ticket& ticket) const = 0;
};

class Ticket {
public:
    Ticket();

    std::string assign() { return state_->assign(*this); }
    std::string close() { return state_->close(*this); }
    std::string status() const { return state_->name(); }
    // 状态迁移集中替换当前状态对象，旧状态随 unique_ptr 自动销毁。
    void transition_to(std::unique_ptr<TicketState> state) { state_ = std::move(state); }

private:
    std::unique_ptr<TicketState> state_;
};

class AssignedState final : public TicketState {
public:
    std::string name() const override { return "assigned"; }
    std::string assign(Ticket&) const override { return "ignored"; }
    std::string close(Ticket& ticket) const override;
};

class ClosedState final : public TicketState {
public:
    std::string name() const override { return "closed"; }
    std::string assign(Ticket&) const override { return "ignored"; }
    std::string close(Ticket&) const override { return "ignored"; }
};

class OpenState final : public TicketState {
public:
    std::string name() const override { return "open"; }
    std::string assign(Ticket& ticket) const override {
        ticket.transition_to(std::make_unique<AssignedState>());
        return "assigned";
    }
    std::string close(Ticket&) const override { return "ignored"; }
};

inline Ticket::Ticket() : state_(std::make_unique<OpenState>()) {}

inline std::string AssignedState::close(Ticket& ticket) const {
    ticket.transition_to(std::make_unique<ClosedState>());
    return "closed";
}

} // namespace state::after
