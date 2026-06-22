/*
测试目的：展示没有 Command 时，调用方如何直接执行并手工撤销编辑操作。
测试步骤：追加两段文本，再由调用方计算长度并调用 erase_last。
通过含义：Editor 基础行为正确；但撤销知识泄漏到了调用方，无法统一保存操作历史。
*/

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
