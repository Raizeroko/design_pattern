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

// Editor 回归为纯粹的命令接收者，只负责实际修改文本。
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
    // execute 表示用户执行操作，undo 表示该操作的反向行为。
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class AppendTextCommand final : public Command {
public:
    // 一个命令同时记录目标编辑器和本次用户输入的文本。
    AppendTextCommand(Editor& editor, std::string text)
        : editor_(editor), text_(std::move(text)) {}

    // 执行时把保存的文本交给编辑器。
    void execute() override { editor_.append(text_); }
    // 撤销所需长度由命令自己保存，调用方无需重新推算。
    void undo() override { editor_.erase_last(text_.size()); }

private:
    // 非拥有引用：Editor 必须比命令和历史记录活得更久。
    Editor& editor_;
    std::string text_;
};

// 调用方只把命令交给历史记录，不再手工维护撤销信息。
class CommandHistory {
public:
    void execute(std::unique_ptr<Command> command) {
        // 先真正执行用户操作，成功后再把命令放进历史栈。
        command->execute();
        history_.push_back(std::move(command));
    }

    void undo_last() {
        // 没有历史时撤销是安全的空操作。
        if (history_.empty()) {
            return;
        }
        // 栈顶就是最近一次操作，撤销后将其从历史中移除。
        history_.back()->undo();
        history_.pop_back();
    }

private:
    // unique_ptr 表示历史记录拥有这些命令对象。
    std::vector<std::unique_ptr<Command>> history_;
};

} // namespace command::after
