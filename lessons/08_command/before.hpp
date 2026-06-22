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

class Editor {
public:
    void append(const std::string& text) { text_ += text; }
    void erase_last(int count) { text_.erase(text_.size() - static_cast<std::size_t>(count)); }
    const std::string& text() const { return text_; }

private:
    std::string text_;
};

} // namespace command::before
