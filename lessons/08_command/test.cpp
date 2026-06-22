#include "practice.hpp"

#include <iostream>
#include <memory>

int main() {
    int failures = 0;
    auto check = [&](bool passed, const char* message) {
        std::cout << (passed ? "[PASS] " : "[FAIL] ") << message << '\n';
        failures += passed ? 0 : 1;
    };

    command::practice::Editor editor;
    command::practice::CommandHistory history;
    history.execute(std::make_unique<command::practice::AppendTextCommand>(
        editor, "hello"));
    history.execute(std::make_unique<command::practice::AppendTextCommand>(
        editor, " world"));
    check(editor.text() == "hello world", "commands should execute in order");

    history.undo_last();
    check(editor.text() == "hello", "undo should revert the latest command");

    return failures == 0 ? 0 : 1;
}

