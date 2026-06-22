#pragma once

/*
场景：咖啡可以动态组合牛奶、糖浆、燕麦奶等加料，每种加料影响价格和描述。
新需求：加料种类与组合数量会持续增加。
当前问题：
1. 每个加料对应一个 bool，参数含义不直观。
2. 所有组合逻辑集中在一个函数，增加加料必须修改原函数。
3. 若用子类表达所有组合，会产生数量爆炸。
练习目标：在运行时逐层组合职责，而不修改基础饮品。
*/

#include <string>

namespace decorator::before {

inline int coffee_price(bool milk, bool syrup) {
    int price = 12;
    if (milk) {
        price += 3;
    }
    if (syrup) {
        price += 2;
    }
    return price;
}

} // namespace decorator::before
