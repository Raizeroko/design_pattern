#pragma once

/*
场景：文本编辑器需要执行追加文本，并逐步支持撤销、重放和操作日志。
新需求：记录操作历史并撤销最后一次操作。
当前问题：
1. 调用方直接操作 Editor，没有可保存的“操作对象”。
2. 撤销逻辑只能由调用方手工推断，无法统一管理。
3. 新操作会带来新的历史记录和撤销分支。
练习目标：把操作封装为对象，让执行者统一执行并管理历史。
*/

#include <string>

namespace command::before {

// Editor 只提供文本操作，本身不知道哪些操作需要进入历史记录。
class Editor {
public:
    // 用户输入文本时，调用方直接修改编辑器。
    void append(const std::string& text) { text_ += text; }
    // 撤销时调用方必须自己记住上次追加了多少字符。
    void erase_last(int count) { text_.erase(text_.size() - static_cast<std::size_t>(count)); }
    // 界面读取当前文本用于显示。
    const std::string& text() const { return text_; }

private:
    // 编辑器当前持有的文档内容。
    std::string text_;
};

} // namespace command::before
