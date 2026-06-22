#include "before.hpp"

#include <iostream>

int main() {
    command::before::Editor editor;
    editor.append("hello");
    editor.append(" world");
    const bool appended = editor.text() == "hello world";
    editor.erase_last(6);
    const bool manually_undone = editor.text() == "hello";

    std::cout << (appended ? "[PASS] " : "[FAIL] ")
              << "editor should append text\n";
    std::cout << (manually_undone ? "[PASS] " : "[FAIL] ")
              << "caller can manually erase the latest text\n";
    return appended && manually_undone ? 0 : 1;
}

