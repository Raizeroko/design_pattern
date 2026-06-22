#pragma once

#include <stdexcept>
#include <string>

namespace strategy::my {

class shipping_strategy{
public:
    virtual int shipping_fee(int distance_km, bool vip) const = 0;
    virtual ~shipping_strategy() = default;
};

class standard_shipping_strategy : public shipping_strategy{
public:
    int shipping_fee(int distance_km, bool vip) const override {
        return vip ? distance_km * 2 : 10 + distance_km * 2;
    }
};

class express_shipping_strategy : public shipping_strategy{
public:
    int shipping_fee(int distance_km, bool vip) const override {
        return vip ? distance_km * 4 : 20 + distance_km * 4;
    }
};

class shipping_context{
public:
    shipping_context(shipping_strategy* s) : strategy_(s) {}
    int get_shipping_fee(int distance_km, bool vip) {
        return strategy_->shipping_fee(distance_km, vip);
    }
private:
    shipping_strategy* strategy_;
};

} // namespace strategy::my