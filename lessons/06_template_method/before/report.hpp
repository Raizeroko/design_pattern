#pragma once

#include <string>
#include <vector>

namespace template_method::before {

inline std::string export_csv(const std::vector<int>& rows) {
    std::string out = "begin\n";
    for (int row : rows) {
        out += std::to_string(row) + "\n";
    }
    out += "end";
    return out;
}

} // namespace template_method::before
