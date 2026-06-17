#pragma once

#include <map>
#include <string>

namespace singleton::before {

inline std::string read_config(std::map<std::string, std::string>& config, const std::string& key) {
    return config[key];
}

} // namespace singleton::before
