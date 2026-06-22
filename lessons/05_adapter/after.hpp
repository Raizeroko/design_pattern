#pragma once

/*
参考重构：Adapter
- PaymentPort 是业务层真正需要的稳定支付接口。
- LegacyPayAdapter 持有旧 SDK，并把 do_pay 的字符串结果转换为 bool。
- checkout 只认识 PaymentPort，第三方 SDK 的类型和协议被限制在适配器内部。
适配器只做语义映射；重试、日志等业务策略不应偷偷塞进这里。
*/

#include <string>

namespace adapter::after {

// 第三方 SDK 保持原样；适配器模式不要求修改外部依赖。
class LegacyPaySdk {
public:
    std::string do_pay(int cents) const {
        return cents > 0 ? "OK" : "FAIL";
    }
};

// 这是业务层定义的接口，而不是第三方 SDK 强加给业务层的接口。
struct PaymentPort {
    virtual ~PaymentPort() = default;
    // bool 是结账业务真正需要的支付语义。
    virtual bool pay(int cents) const = 0;
};

// 适配器在边界处完成方法名和返回值语义的翻译。
class LegacyPayAdapter final : public PaymentPort {
public:
    bool pay(int cents) const override {
        // 在系统边界把第三方字符串协议翻译成内部布尔协议。
        return sdk_.do_pay(cents) == "OK";
    }

private:
    // SDK 被封装在适配器内部，不会泄漏到 checkout 调用方。
    LegacyPaySdk sdk_;
};

// 结账可接收任何 PaymentPort，例如旧 SDK、测试替身或新支付渠道。
inline bool checkout(const PaymentPort& payment, int cents) {
    return payment.pay(cents);
}

} // namespace adapter::after
