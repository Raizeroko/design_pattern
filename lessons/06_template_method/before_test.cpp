/*
测试目的：锁定旧 CSV 导出的完整输出顺序。
测试步骤：导出两行数据，精确比较头部、数据行、换行和尾部。
通过含义：重构后必须保持既有 CSV 文本完全一致，不能只验证部分字符串。
*/

#include "before.hpp"

#include <iostream>

int main() {
    const bool ok =
        template_method::before::export_csv({1, 2}) == "begin\n1\n2\nend";
    std::cout << (ok ? "[PASS] " : "[FAIL] ")
              << "legacy CSV export should preserve the full flow\n";
    return ok ? 0 : 1;
}
