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

