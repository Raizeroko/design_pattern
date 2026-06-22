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

/*
概念与代码对照：
- [完整流程] export_csv。
- [固定步骤] 写入 "begin"、写入 "end"。
- [变化步骤] for 循环中的 CSV 行格式。
- [问题证据] 固定步骤和变化步骤混在一个函数；新增格式容易复制整段流程。
*/

namespace template_method::before {

// [完整流程] export_csv 同时定义固定流程和 CSV 变化步骤。
inline std::string export_csv(const std::vector<int>& rows) {
    // [固定步骤 1] 所有报表先写头部。
    std::string out = "begin\n";
    // [变化步骤] CSV 把每个数字写成一行文本。
    for (int row : rows) {
        out += std::to_string(row) + "\n";
    }
    // [固定步骤 2] 所有报表最后写尾部。
    out += "end";
    return out;
}

} // namespace template_method::before
