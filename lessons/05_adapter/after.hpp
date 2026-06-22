#pragma once

/*
参考重构：Adapter
- PaymentPort 是业务层真正需要的稳定支付接口。
- LegacyPayAdapter 持有旧 SDK，并把 do_pay 的字符串结果转换为 bool。
- checkout 只认识 PaymentPort，第三方 SDK 的类型和协议被限制在适配器内部。
适配器只做语义映射；重试、日志等业务策略不应偷偷塞进这里。
*/

#include <string>

/*
模式角色与代码对照：
- [Adaptee] LegacyPaySdk。
- [Target / 目标接口] PaymentPort::pay，返回业务需要的 bool。
- [Adapter] LegacyPayAdapter。
- [转换动作] Adapter::pay 调用 do_pay 并把字符串转换成 bool。
- [Client] checkout，只依赖 PaymentPort。
*/

namespace adapter::after {

// [Adaptee] 第三方 SDK 保持原样。
class LegacyPaySdk {
public:
    std::string do_pay(int cents) const {
        return cents > 0 ? "OK" : "FAIL";
    }
};

// [Target / 目标接口] 业务层期望使用的 bool pay。
struct PaymentPort {
    virtual ~PaymentPort() = default;
    // [目标动作] 所有支付渠道对业务层统一暴露 pay。
    virtual bool pay(int cents) const = 0;
};

// [Adapter] 同时认识 Target 和 Adaptee，负责二者转换。
class LegacyPayAdapter final : public PaymentPort {
public:
    bool pay(int cents) const override {
        // [转换动作] 调用 do_pay，并把 "OK"/"FAIL" 翻译为 bool。
        return sdk_.do_pay(cents) == "OK";
    }

private:
    // [Adapter 持有 Adaptee] LegacyPaySdk 不再暴露给 Client。
    LegacyPaySdk sdk_;
};

// [Client] checkout 只依赖 Target，不知道 LegacyPaySdk。
inline bool checkout(const PaymentPort& payment, int cents) {
    return payment.pay(cents);
}

} // namespace adapter::after
