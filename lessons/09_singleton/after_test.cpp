#include "after.hpp"

#include <iostream>

int main() {
    auto& config = singleton::after::AppConfig::instance();
    config.clear_for_test();
    config.set("env", "prod");

    const bool value_ok = config.get("env") == "prod";
    const bool identity_ok =
        &config == &singleton::after::AppConfig::instance();
    std::cout << (value_ok ? "[PASS] " : "[FAIL] ")
              << "shared config should retain values\n";
    std::cout << (identity_ok ? "[PASS] " : "[FAIL] ")
              << "instance should return the same object\n";
    return value_ok && identity_ok ? 0 : 1;
}

