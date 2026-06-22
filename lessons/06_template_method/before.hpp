#pragma once

/*
场景：所有报表导出都遵循“写头部、格式化数据、写尾部”的固定流程。
新需求：增加 JSON Lines 等格式，但流程顺序不能变化。
当前问题：
1. 每种格式都可能复制完整导出流程。
2. 复制后容易漏掉头部、尾部或改变步骤顺序。
3. 真正变化的只有行格式，却无法单独替换。
练习目标：固定流程骨架，只开放必要步骤给具体格式实现。
*/

#include <string>
#include <vector>

namespace template_method::before {

inline std::string export_csv(const std::vector<int>& rows) {
    std::string out = "begin\n";
    for (int row : rows) {
        out += std::to_string(row) + "\n";
    }
    out += "end";
    return out;
}

} // namespace template_method::before
