#pragma once

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
