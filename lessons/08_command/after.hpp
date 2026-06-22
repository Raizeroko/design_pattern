#pragma once

/*
参考重构：Command
- Command 把 execute 与 undo 统一成可保存的操作对象。
- AppendTextCommand 保存接收者 Editor 和撤销所需的文本长度。
- CommandHistory 负责执行、保存和逆序撤销，Editor 不需要知道历史机制。
命令保存 Editor 引用，因此命令历史不能比 Editor 活得更久。
*/

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

// 操作被提升为对象后，才可以保存、排队、重放和撤销。
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

// 调用方只把命令交给历史记录，不再手工维护撤销信息。
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
