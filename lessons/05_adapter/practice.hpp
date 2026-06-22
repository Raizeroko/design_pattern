#pragma once

#include <string>

namespace adapter::practice {

class LegacyPaySdk {
public:
    std::string do_pay(int cents) const { return cents > 0 ? "OK" : "FAIL"; }
};

struct PaymentPort {
    virtual ~PaymentPort() = default;
    virtual bool pay(int cents) const = 0;
};

class LegacyPayAdapter final : public PaymentPort {
public:
    bool pay(int) const override { return false; /* TODO */ }
};

} // namespace adapter::practice

