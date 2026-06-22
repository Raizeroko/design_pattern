#include "before.hpp"

#include <iostream>

int main() {
    const bool ok =
        template_method::before::export_csv({1, 2}) == "begin\n1\n2\nend";
    std::cout << (ok ? "[PASS] " : "[FAIL] ")
              << "legacy CSV export should preserve the full flow\n";
    return ok ? 0 : 1;
}

