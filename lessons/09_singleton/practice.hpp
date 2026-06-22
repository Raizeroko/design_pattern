#pragma once

#include <string>

namespace singleton::practice {

class AppConfig {
public:
    static AppConfig& instance() {
        static AppConfig config;
        return config;
    }

    void set(std::string, std::string) { /* TODO */ }
    std::string get(const std::string&) const { return {}; /* TODO */ }
    void clear_for_test() { /* TODO */ }

private:
    AppConfig() = default;
};

} // namespace singleton::practice

