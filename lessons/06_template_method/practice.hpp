#pragma once

#include <string>
#include <vector>

namespace template_method::practice {

class ReportExporter {
public:
    virtual ~ReportExporter() = default;

    std::string export_report(const std::vector<int>& rows) const {
        return "begin\n" + format_rows(rows) + "end";
    }

private:
    virtual std::string format_rows(const std::vector<int>& rows) const = 0;
};

class JsonLinesExporter final : public ReportExporter {
private:
    std::string format_rows(const std::vector<int>&) const override {
        return {}; // TODO: format every row.
    }
};

} // namespace template_method::practice

