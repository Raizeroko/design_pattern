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

/*
模式角色与代码对照：
- [Context] Ticket。
- [State] TicketState。
- [ConcreteState] OpenState、AssignedState、ClosedState。
- [委托动作] Ticket::assign/close 调用 state_->assign/close。
- [迁移动作] ConcreteState 调用 ticket.transition_to(...)。
*/

namespace state::after {

class Ticket;

// [State] 定义每个状态都必须回答的操作。
struct TicketState {
    virtual ~TicketState() = default;
    // [状态查询动作] Context 通过 name 获取当前状态名称。
    virtual std::string name() const = 0;
    // [状态行为] assign/close 的具体结果由 ConcreteState 决定。
    virtual std::string assign(Ticket& ticket) const = 0;
    virtual std::string close(Ticket& ticket) const = 0;
};

class Ticket {
public:
    // [初始状态] 新 Context 默认持有 OpenState。
    Ticket();

    // [委托动作] Context 把操作转发给当前 State。
    std::string assign() { return state_->assign(*this); }
    std::string close() { return state_->close(*this); }
    std::string status() const { return state_->name(); }
    // [迁移动作] ConcreteState 通过本方法替换 Context 当前状态。
    void transition_to(std::unique_ptr<TicketState> state) { state_ = std::move(state); }

private:
    // [Context-State 关系] Ticket 在任一时刻持有一个 State。
    std::unique_ptr<TicketState> state_;
};

// [ConcreteState: Assigned] 重复领取无效，允许关闭。
class AssignedState final : public TicketState {
public:
    std::string name() const override { return "assigned"; }
    std::string assign(Ticket&) const override { return "ignored"; }
    std::string close(Ticket& ticket) const override;
};

// [ConcreteState: Closed] 终态，所有操作都忽略。
class ClosedState final : public TicketState {
public:
    std::string name() const override { return "closed"; }
    std::string assign(Ticket&) const override { return "ignored"; }
    std::string close(Ticket&) const override { return "ignored"; }
};

// [ConcreteState: Open] 允许 assign，拒绝直接 close。
class OpenState final : public TicketState {
public:
    std::string name() const override { return "open"; }
    std::string assign(Ticket& ticket) const override {
        // [迁移动作] OpenState 决定下一状态是 AssignedState。
        ticket.transition_to(std::make_unique<AssignedState>());
        return "assigned";
    }
    std::string close(Ticket&) const override { return "ignored"; }
};

// [初始化动作] Context 创建时安装 OpenState。
inline Ticket::Ticket() : state_(std::make_unique<OpenState>()) {}

inline std::string AssignedState::close(Ticket& ticket) const {
    // [迁移动作] AssignedState 决定下一状态是 ClosedState。
    ticket.transition_to(std::make_unique<ClosedState>());
    return "closed";
}

} // namespace state::after
