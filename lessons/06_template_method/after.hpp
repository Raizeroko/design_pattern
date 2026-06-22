#pragma once

/*
参考重构：Template Method
- export_report 是不可被子类改写的公开流程骨架，固定头部、数据、尾部顺序。
- format_rows 是唯一变化点，由具体导出器实现。
- CsvExporter 与 JsonLinesExporter 复用流程，但各自控制行格式。
当流程本身也频繁变化时，组合多个步骤策略通常比继承更灵活。
*/

#include <sstream>
#include <string>
#include <vector>

namespace template_method::after {

// ReportExporter 表达所有报表共享的业务流程。
class ReportExporter {
public:
    virtual ~ReportExporter() = default;

    // 模板方法固定执行顺序，子类不能跳过头部或尾部。
    std::string export_report(const std::vector<int>& rows) const {
        // 先头部、再数据、最后尾部的顺序只在这里定义一次。
        return header() + format_rows(rows) + footer();
    }

private:
    // 只把真正变化的步骤留给子类。
    virtual std::string format_rows(const std::vector<int>& rows) const = 0;

    // 头尾是所有格式共同遵守的协议，不开放给子类随意修改。
    std::string header() const { return "begin\n"; }
    std::string footer() const { return "end"; }
};

// CSV 导出器只回答“每一行如何表示”。
class CsvExporter final : public ReportExporter {
private:
    std::string format_rows(const std::vector<int>& rows) const override {
        std::string out;
        for (int row : rows) {
            // CSV 场景中，一个数字占一行。
            out += std::to_string(row) + "\n";
        }
        return out;
    }
};

// JSON Lines 复用相同流程，只替换数据行格式。
class JsonLinesExporter final : public ReportExporter {
private:
    std::string format_rows(const std::vector<int>& rows) const override {
        std::string out;
        for (int row : rows) {
            // 每一行都是独立 JSON 对象，头部和尾部无需在这里重复。
            out += "{\"value\":" + std::to_string(row) + "}\n";
        }
        return out;
    }
};

} // namespace template_method::after
