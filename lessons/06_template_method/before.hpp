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

// CSV 导出函数同时定义整个导出流程和 CSV 的行格式。
inline std::string export_csv(const std::vector<int>& rows) {
    // 所有报表都必须先写固定头部。
    std::string out = "begin\n";
    // 这里真正属于 CSV 的变化点，是把每个数字写成一行文本。
    for (int row : rows) {
        out += std::to_string(row) + "\n";
    }
    // 所有报表都必须以固定尾部结束；复制新导出函数时很容易漏掉。
    out += "end";
    return out;
}

} // namespace template_method::before
