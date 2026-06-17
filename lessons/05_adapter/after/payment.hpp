#pragma once

#include <string>

namespace adapter::after {

class LegacyPaySdk {
public:
    std::string do_pay(int cents) const {
        return cents > 0 ? "OK" : "FAIL";
    }
};

struct PaymentPort {
    virtual ~PaymentPort() = default;
    virtual bool pay(int cents) const = 0;
};

class LegacyPayAdapter final : public PaymentPort {
public:
    bool pay(int cents) const override {
        return sdk_.do_pay(cents) == "OK";
    }

private:
    LegacyPaySdk sdk_;
};

inline bool checkout(const PaymentPort& payment, int cents) {
    return payment.pay(cents);
}

} // namespace adapter::after
