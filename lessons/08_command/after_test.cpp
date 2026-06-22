/*
测试目的：验证命令可以被统一执行、保存，并由历史记录撤销。
测试步骤：历史记录执行两个 AppendTextCommand，再撤销最后一个命令。
通过含义：调用方不需要计算删除长度，撤销所需状态由具体命令保存。
*/

#include "after.hpp"

#include <iostream>
#include <memory>

int main() {
    command::after::Editor editor;
    command::after::CommandHistory history;
    history.execute(std::make_unique<command::after::AppendTextCommand>(
        editor, "hello"));
    history.execute(std::make_unique<command::after::AppendTextCommand>(
        editor, " world"));
    const bool executed = editor.text() == "hello world";
    history.undo_last();
    const bool undone = editor.text() == "hello";

    std::cout << (executed ? "[PASS] " : "[FAIL] ")
              << "history should execute commands in order\n";
    std::cout << (undone ? "[PASS] " : "[FAIL] ")
              << "history should undo the latest command\n";
    return executed && undone ? 0 : 1;
}
