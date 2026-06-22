#include "practice.hpp"

#include <iostream>

int main() {
    int failures = 0;
    auto check = [&](bool passed, const char* message) {
        std::cout << (passed ? "[PASS] " : "[FAIL] ") << message << '\n';
        failures += passed ? 0 : 1;
    };

    template_method::practice::JsonLinesExporter exporter;
    check(exporter.export_report({7}) == "begin\n{\"value\":7}\nend",
          "template should preserve the flow and replace only row formatting");
    check(exporter.export_report({1, 2}) ==
              "begin\n{\"value\":1}\n{\"value\":2}\nend",
          "formatter should handle every row");

    return failures == 0 ? 0 : 1;
}

