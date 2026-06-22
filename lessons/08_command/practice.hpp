#pragma once

#include <memory>
#include <string>
#include <utility>

namespace command::practice {

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

    void execute() override { /* TODO */ }
    void undo() override { /* TODO */ }

private:
    Editor& editor_;
    std::string text_;
};

class CommandHistory {
public:
    void execute(std::unique_ptr<Command>) { /* TODO */ }
    void undo_last() { /* TODO */ }
};

} // namespace command::practice

