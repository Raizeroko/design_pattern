#pragma once

/*
场景：结账模块根据配送方式和距离计算运费，VIP 可以免除基础费用。
新需求：配送方式会持续增加，例如当日达、冷链、大件配送。
当前问题：
1. method 使用字符串，拼写错误只能在运行时发现。
2. 每增加一种算法都要修改 shipping_fee，分支会持续膨胀。
3. 结账流程同时承担“选择算法”和“执行算法”两个职责。
练习目标：在 practice.hpp 中让算法可以独立扩展，并保持现有计费规则。
*/

#include <stdexcept>
#include <string>

namespace strategy::before {

inline int shipping_fee(const std::string& method, int distance_km, bool vip) {
    if (method == "standard") {
        return vip ? distance_km * 2 : 10 + distance_km * 2;
    }
    if (method == "express") {
        return vip ? distance_km * 4 : 20 + distance_km * 4;
    }
    throw std::invalid_argument("unknown shipping method");
}

} // namespace strategy::before
