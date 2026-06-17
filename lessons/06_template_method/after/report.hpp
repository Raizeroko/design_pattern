#pragma once

#include <sstream>
#include <string>
#include <vector>

namespace template_method::after {

class ReportExporter {
public:
    virtual ~ReportExporter() = default;

    std::string export_report(const std::vector<int>& rows) const {
        return header() + format_rows(rows) + footer();
    }

private:
    virtual std::string format_rows(const std::vector<int>& rows) const = 0;

    std::string header() const { return "begin\n"; }
    std::string footer() const { return "end"; }
};

class CsvExporter final : public ReportExporter {
private:
    std::string format_rows(const std::vector<int>& rows) const override {
        std::string out;
        for (int row : rows) {
            out += std::to_string(row) + "\n";
        }
        return out;
    }
};

class JsonLinesExporter final : public ReportExporter {
private:
    std::string format_rows(const std::vector<int>& rows) const override {
        std::string out;
        for (int row : rows) {
            out += "{\"value\":" + std::to_string(row) + "}\n";
        }
        return out;
    }
};

} // namespace template_method::after
