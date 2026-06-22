/*
测试目的：验证装饰器可以按运行时顺序组合价格和描述。
测试步骤：从 Coffee 开始，依次包装 Milk 和 OatMilk，再读取最终结果。
通过含义：每层只增加自己的职责，新加料无需修改 Coffee 或已有装饰器。
*/

#include "after.hpp"

#include <iostream>
#include <memory>
#include <utility>

int main() {
    std::unique_ptr<decorator::after::Drink> drink =
        std::make_unique<decorator::after::Coffee>();
    drink = std::make_unique<decorator::after::Milk>(std::move(drink));
    drink = std::make_unique<decorator::after::OatMilk>(std::move(drink));

    const bool price_ok = drink->price() == 20;
    const bool name_ok = drink->name() == "coffee+milk+oat";
    std::cout << (price_ok ? "[PASS] " : "[FAIL] ")
              << "decorators should accumulate price\n";
    std::cout << (name_ok ? "[PASS] " : "[FAIL] ")
              << "decorators should compose description\n";
    return price_ok && name_ok ? 0 : 1;
}
