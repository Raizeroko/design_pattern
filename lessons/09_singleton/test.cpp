#include "practice.hpp"

#include <iostream>

int main() {
    int failures = 0;
    auto check = [&](bool passed, const char* message) {
        std::cout << (passed ? "[PASS] " : "[FAIL] ") << message << '\n';
        failures += passed ? 0 : 1;
    };

    auto& config = singleton::practice::AppConfig::instance();
    config.clear_for_test();
    config.set("env", "prod");

    check(config.get("env") == "prod", "stored config should be readable");
    check(&config == &singleton::practice::AppConfig::instance(),
          "instance() should return the same object");

    return failures == 0 ? 0 : 1;
}

