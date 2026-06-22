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

/*
概念与代码对照：
- [Receiver / 接收者] Editor，真正修改文本。
- [请求动作] 调用方直接调用 append。
- [撤销动作] 调用方直接调用 erase_last，并自己提供字符数。
- [问题证据] 没有表示“一次操作”的对象，执行和撤销信息无法放入历史记录。
*/

#include <string>

namespace command::before {

// [Receiver / 接收者] Editor 真正执行文本修改。
class Editor {
public:
    // [执行动作] 调用方直接请求 Receiver 追加文本。
    void append(const std::string& text) { text_ += text; }
    // [撤销动作] 调用方直接请求 Receiver 删除，并自己计算字符数。
    void erase_last(int count) { text_.erase(text_.size() - static_cast<std::size_t>(count)); }
    // [查询动作] 界面读取 Receiver 当前内容。
    const std::string& text() const { return text_; }

private:
    // [Receiver 状态] 当前文档内容。
    std::string text_;
};

} // namespace command::before
