#include "lessons/08_command/after/editor.hpp"
#include "lessons/08_command/before/editor.hpp"
#include "tests/test_framework.hpp"

#include <memory>

void command_tests() {
    command::before::Editor legacy;
    legacy.append("hi");
    legacy.erase_last(1);
    EXPECT_EQ(legacy.text(), "h");

    command::after::Editor editor;
    command::after::CommandHistory history;
    history.execute(std::make_unique<command::after::AppendTextCommand>(editor, "hello"));
    history.execute(std::make_unique<command::after::AppendTextCommand>(editor, " world"));
    EXPECT_EQ(editor.text(), "hello world");
    history.undo_last();
    EXPECT_EQ(editor.text(), "hello");
}

int main() {
    return labtest::run("command", command_tests);
}
