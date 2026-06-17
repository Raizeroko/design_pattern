#include "lessons/06_template_method/after/report.hpp"
#include "lessons/06_template_method/before/report.hpp"
#include "tests/test_framework.hpp"

#include <vector>

void template_method_tests() {
    EXPECT_EQ(template_method::before::export_csv({1, 2}), "begin\n1\n2\nend");
    template_method::after::JsonLinesExporter exporter;
    EXPECT_EQ(exporter.export_report({7}), "begin\n{\"value\":7}\nend");
}

int main() {
    return labtest::run("template_method", template_method_tests);
}
