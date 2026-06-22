#pragma once

/*
场景：结账业务希望所有支付渠道都提供 bool pay(int cents)，但旧 SDK 返回 "OK"/"FAIL"。
新需求：接入旧 SDK，同时不让第三方接口污染业务层。
当前问题：
1. 业务代码直接创建 LegacyPaySdk，并理解它的字符串协议。
2. SDK 接口变化会迫使所有调用方修改。
3. 内部的支付语义与第三方语义没有清晰边界。
练习目标：通过适配层完成接口和返回值语义转换。
*/

#include <string>

/*
概念与代码对照：
- [Adaptee / 被适配者] LegacyPaySdk。
- [不兼容接口] do_pay(int) 返回 "OK"/"FAIL"。
- [Client / 调用方] checkout_with_legacy_sdk。
- [手工转换动作] sdk.do_pay(cents) == "OK"。
- [问题证据] 业务函数直接知道 SDK 类型、方法名和返回协议。
*/

namespace adapter::before {

// [Adaptee / 被适配者] 无法按业务需要直接修改的旧支付 SDK。
class LegacyPaySdk {
public:
    // [不兼容接口] do_pay 返回字符串，而业务需要 bool pay。
    std::string do_pay(int cents) const {
        return cents > 0 ? "OK" : "FAIL";
    }
};

// [Client / 调用方] 结账业务直接依赖 Adaptee 并手工转换协议。
inline bool checkout_with_legacy_sdk(int cents) {
    LegacyPaySdk sdk;
    return sdk.do_pay(cents) == "OK";
}

} // namespace adapter::before
