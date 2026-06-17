#pragma once

#include <memory>
#include <string>
#include <utility>

namespace state::after {

class Ticket;

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
