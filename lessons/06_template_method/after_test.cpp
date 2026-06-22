/*
测试目的：验证模板方法固定流程，同时允许子类替换行格式。
测试步骤：
1. CsvExporter 必须保持旧输出。
2. JsonLinesExporter 必须复用相同头尾，只改变每一行的格式。
通过含义：稳定流程位于基类，变化步骤由具体导出器负责。
*/

#include "after.hpp"

#include <iostream>

int main() {
    template_method::after::CsvExporter csv;
    template_method::after::JsonLinesExporter json;

    const bool csv_ok = csv.export_report({1, 2}) == "begin\n1\n2\nend";
    const bool json_ok =
        json.export_report({7}) == "begin\n{\"value\":7}\nend";
    std::cout << (csv_ok ? "[PASS] " : "[FAIL] ")
              << "template should preserve existing CSV behavior\n";
    std::cout << (json_ok ? "[PASS] " : "[FAIL] ")
              << "subclass should replace only row formatting\n";
    return csv_ok && json_ok ? 0 : 1;
}
