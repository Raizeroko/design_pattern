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

// 结账页面把用户选择的配送方式、配送距离和会员身份一起传进来。
// 这个函数既负责识别配送方式，又负责执行对应公式，所以会成为变化中心。
inline int shipping_fee(const std::string& method, int distance_km, bool vip) {
    // 标准配送：普通用户收 10 元起步价，每公里 2 元；VIP 免起步价。
    if (method == "standard") {
        return vip ? distance_km * 2 : 10 + distance_km * 2;
    }
    // 加急配送：价格更高，但会员优惠规则仍混在同一个函数中。
    if (method == "express") {
        return vip ? distance_km * 4 : 20 + distance_km * 4;
    }
    // 字符串不受类型系统保护，拼错的配送方式只能运行到这里才被发现。
    throw std::invalid_argument("unknown shipping method");
}

} // namespace strategy::before
