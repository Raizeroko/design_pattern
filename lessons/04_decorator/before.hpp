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

/*
概念与代码对照：
- [基础对象] price 初始值 12 代表基础咖啡。
- [可选职责] milk、syrup 两个布尔参数。
- [组合动作] if (milk/syrup) 决定叠加哪些职责。
- [问题证据] 新增加料必须修改函数参数和函数内部分支。
*/

namespace decorator::before {

// [调用方输入] milk、syrup 用布尔值描述要组合的加料。
inline int coffee_price(bool milk, bool syrup) {
    // [基础对象] price=12 表示未加料咖啡。
    int price = 12;
    // [可选职责 1] milk 分支把牛奶职责写进基础函数。
    if (milk) {
        price += 3;
    }
    // [可选职责 2] syrup 分支继续扩大基础函数。
    if (syrup) {
        price += 2;
    }
    return price;
}

} // namespace decorator::before
