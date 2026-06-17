#pragma once

#include <map>
#include <string>
#include <utility>

namespace singleton::after {

class AppConfig {
public:
    static AppConfig& instance() {
        static AppConfig config;
        return config;
    }

    void set(std::string key, std::string value) {
        values_[std::move(key)] = std::move(value);
    }

    std::string get(const std::string& key) const {
        auto found = values_.find(key);
        return found == values_.end() ? "" : found->second;
    }

    void clear_for_test() {
        values_.clear();
    }

private:
    AppConfig() = default;
    std::map<std::string, std::string> values_;
};

} // namespace singleton::after
