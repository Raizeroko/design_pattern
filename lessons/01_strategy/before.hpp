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

/*
概念与代码对照：
- [调用方输入] method、distance_km、vip。
- [策略选择动作] if (method == ...)。
- [具体算法] 每个 return 中的计费公式。
- [问题证据] 选择与算法都在 shipping_fee；新增配送方式必须修改该函数。
*/

namespace strategy::before {

// [调用方输入] 结账页面传入配送方式、距离和会员身份。
// [问题证据] shipping_fee 同时执行“选择策略”和“计算费用”两个动作。
inline int shipping_fee(const std::string& method, int distance_km, bool vip) {
    // [具体算法 1] standard：10 元起步价 + 每公里 2 元；VIP 免起步价。
    if (method == "standard") {
        return vip ? distance_km * 2 : 10 + distance_km * 2;
    }
    // [具体算法 2] express：20 元起步价 + 每公里 4 元；VIP 免起步价。
    if (method == "express") {
        return vip ? distance_km * 4 : 20 + distance_km * 4;
    }
    // [问题证据] 字符串不受类型系统保护，拼错只能运行到这里才发现。
    throw std::invalid_argument("unknown shipping method");
}

} // namespace strategy::before
