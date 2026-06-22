#pragma once

/*
参考重构：Command
- Command 把 execute 与 undo 统一成可保存的操作对象。
- AppendTextCommand 保存接收者 Editor 和撤销所需的文本长度。
- CommandHistory 负责执行、保存和逆序撤销，Editor 不需要知道历史机制。
命令保存 Editor 引用，因此命令历史不能比 Editor 活得更久。
*/

#include <memory>
/*
模式角色与代码对照：
- [Receiver] Editor。
- [Command] Command。
- [ConcreteCommand] AppendTextCommand。
- [Invoker] CommandHistory。
- [执行动作] history.execute -> command.execute -> editor.append。
- [撤销动作] history.undo_last -> command.undo -> editor.erase_last。
*/

#include <string>
#include <utility>
#include <vector>

namespace command::after {

// [Receiver] Editor 只负责实际修改文本。
class Editor {
public:
    void append(const std::string& text) { text_ += text; }
    void erase_last(std::size_t count) { text_.erase(text_.size() - count); }
    const std::string& text() const { return text_; }

private:
    std::string text_;
};

// [Command] 把请求抽象为可执行、可撤销的对象。
struct Command {
    virtual ~Command() = default;
    // [命令动作] execute 执行请求，undo 执行反向请求。
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class AppendTextCommand final : public Command {
public:
    // [ConcreteCommand] 保存 Receiver 和本次请求参数。
    AppendTextCommand(Editor& editor, std::string text)
        : editor_(editor), text_(std::move(text)) {}

    // [执行链] ConcreteCommand 调用 Receiver::append。
    void execute() override { editor_.append(text_); }
    // [撤销链] ConcreteCommand 根据自身参数调用 Receiver::erase_last。
    void undo() override { editor_.erase_last(text_.size()); }

private:
    // [Command-Receiver 关系] 非拥有引用，Editor 必须活得更久。
    Editor& editor_;
    std::string text_;
};

// [Invoker / 调用者] CommandHistory 触发命令并保存历史。
class CommandHistory {
public:
    void execute(std::unique_ptr<Command> command) {
        // [调用动作] Invoker 调用 Command::execute，再保存命令。
        command->execute();
        history_.push_back(std::move(command));
    }

    void undo_last() {
        // [边界规则] 没有命令时，撤销为空操作。
        if (history_.empty()) {
            return;
        }
        // [撤销动作] Invoker 调用最近 Command::undo 并移出历史。
        history_.back()->undo();
        history_.pop_back();
    }

private:
    // [Invoker-Command 关系] 历史记录拥有命令对象。
    std::vector<std::unique_ptr<Command>> history_;
};

} // namespace command::after
