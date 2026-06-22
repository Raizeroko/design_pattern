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

namespace adapter::before {

class LegacyPaySdk {
public:
    std::string do_pay(int cents) const {
        return cents > 0 ? "OK" : "FAIL";
    }
};

inline bool checkout_with_legacy_sdk(int cents) {
    LegacyPaySdk sdk;
    return sdk.do_pay(cents) == "OK";
}

} // namespace adapter::before
