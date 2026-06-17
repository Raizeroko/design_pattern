#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace command::after {

class Editor {
public:
    void append(const std::string& text) { text_ += text; }
    void erase_last(std::size_t count) { text_.erase(text_.size() - count); }
    const std::string& text() const { return text_; }

private:
    std::string text_;
};

struct Command {
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class AppendTextCommand final : public Command {
public:
    AppendTextCommand(Editor& editor, std::string text)
        : editor_(editor), text_(std::move(text)) {}

    void execute() override { editor_.append(text_); }
    void undo() override { editor_.erase_last(text_.size()); }

private:
    Editor& editor_;
    std::string text_;
};

class CommandHistory {
public:
    void execute(std::unique_ptr<Command> command) {
        command->execute();
        history_.push_back(std::move(command));
    }

    void undo_last() {
        if (history_.empty()) {
            return;
        }
        history_.back()->undo();
        history_.pop_back();
    }

private:
    std::vector<std::unique_ptr<Command>> history_;
};

} // namespace command::after
