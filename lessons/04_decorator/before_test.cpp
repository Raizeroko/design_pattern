/*
测试目的：锁定布尔参数版本的基础价格与加料价格。
测试步骤：分别计算纯咖啡，以及同时加牛奶和糖浆的咖啡。
通过含义：旧函数计算正确；问题在于每增加一种加料都要增加参数和条件分支。
*/

#include "before.hpp"

#include <iostream>

int main() {
    const bool base_ok = decorator::before::coffee_price(false, false) == 12;
    const bool extras_ok = decorator::before::coffee_price(true, true) == 17;
    std::cout << (base_ok ? "[PASS] " : "[FAIL] ")
              << "plain coffee should cost 12\n";
    std::cout << (extras_ok ? "[PASS] " : "[FAIL] ")
              << "boolean extras should be added to the price\n";
    return base_ok && extras_ok ? 0 : 1;
}
