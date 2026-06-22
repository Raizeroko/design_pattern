#pragma once

/*
参考重构：Template Method
- export_report 是不可被子类改写的公开流程骨架，固定头部、数据、尾部顺序。
- format_rows 是唯一变化点，由具体导出器实现。
- CsvExporter 与 JsonLinesExporter 复用流程，但各自控制行格式。
当流程本身也频繁变化时，组合多个步骤策略通常比继承更灵活。
*/

#include <sstream>
/*
模式角色与代码对照：
- [AbstractClass] ReportExporter。
- [TemplateMethod] export_report，固定调用顺序。
- [PrimitiveOperation / 变化步骤] format_rows。
- [ConcreteClass] CsvExporter、JsonLinesExporter。
- [执行动作] 调用 export_report，内部自动拼接 header + format_rows + footer。
*/

#include <string>
#include <vector>

namespace template_method::after {

// [AbstractClass] 定义所有报表共享的流程骨架。
class ReportExporter {
public:
    virtual ~ReportExporter() = default;

    // [TemplateMethod] 对外入口，固定三个步骤的调用顺序。
    std::string export_report(const std::vector<int>& rows) const {
        // [流程编排] 依次执行固定步骤、变化步骤、固定步骤。
        return header() + format_rows(rows) + footer();
    }

private:
    // [PrimitiveOperation] 把唯一变化的行格式留给 ConcreteClass。
    virtual std::string format_rows(const std::vector<int>& rows) const = 0;

    // [固定步骤] header/footer 由 AbstractClass 自己实现。
    std::string header() const { return "begin\n"; }
    std::string footer() const { return "end"; }
};

// [ConcreteClass 1] CsvExporter 实现 CSV 行格式。
class CsvExporter final : public ReportExporter {
private:
    std::string format_rows(const std::vector<int>& rows) const override {
        std::string out;
        for (int row : rows) {
            // [变化步骤实现 1] 一个数字占一行。
            out += std::to_string(row) + "\n";
        }
        return out;
    }
};

// [ConcreteClass 2] JsonLinesExporter 实现 JSON Lines 行格式。
class JsonLinesExporter final : public ReportExporter {
private:
    std::string format_rows(const std::vector<int>& rows) const override {
        std::string out;
        for (int row : rows) {
            // [变化步骤实现 2] 每一行是独立 JSON 对象。
            out += "{\"value\":" + std::to_string(row) + "}\n";
        }
        return out;
    }
};

} // namespace template_method::after
