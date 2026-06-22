#include "before.hpp"

#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, std::string> config{{"env", "dev"}};
    const bool ok =
        singleton::before::read_config(config, "env") == "dev";
    std::cout << (ok ? "[PASS] " : "[FAIL] ")
              << "explicitly passed config should be readable\n";
    return ok ? 0 : 1;
}

