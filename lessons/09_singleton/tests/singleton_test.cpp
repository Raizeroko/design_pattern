#include "lessons/09_singleton/after/config.hpp"
#include "lessons/09_singleton/before/config.hpp"
#include "tests/test_framework.hpp"

#include <map>

void singleton_tests() {
    std::map<std::string, std::string> config{{"env", "dev"}};
    EXPECT_EQ(singleton::before::read_config(config, "env"), "dev");

    auto& app_config = singleton::after::AppConfig::instance();
    app_config.clear_for_test();
    app_config.set("env", "prod");
    EXPECT_EQ(singleton::after::AppConfig::instance().get("env"), "prod");
}

int main() {
    return labtest::run("singleton", singleton_tests);
}
