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

