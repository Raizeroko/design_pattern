/*
测试目的：确认重构前显式传入配置 map 时可以读取值。
测试步骤：调用方创建并持有配置，再把同一个 map 传给读取函数。
通过含义：读取逻辑正确；但每个调用方都必须持有并传递共享配置。
*/

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
