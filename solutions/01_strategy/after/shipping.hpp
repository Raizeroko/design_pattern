#pragma once

#include <memory>
#include <utility>

namespace strategy::after {

struct ShippingStrategy {
    virtual ~ShippingStrategy() = default;
    virtual int fee(int distance_km, bool vip) const = 0;
};

struct StandardShipping final : ShippingStrategy {
    int fee(int distance_km, bool vip) const override {
        return (vip ? 0 : 10) + distance_km * 2;
    }
};

struct ExpressShipping final : ShippingStrategy {
    int fee(int distance_km, bool vip) const override {
        return (vip ? 0 : 20) + distance_km * 4;
    }
};

struct SameDayShipping final : ShippingStrategy {
    int fee(int distance_km, bool vip) const override {
        return (vip ? 15 : 35) + distance_km * 6;
    }
};

class Checkout {
public:
    explicit Checkout(std::unique_ptr<ShippingStrategy> strategy)
        : strategy_(std::move(strategy)) {}

    int shipping_fee(int distance_km, bool vip) const {
        return strategy_->fee(distance_km, vip);
    }

private:
    std::unique_ptr<ShippingStrategy> strategy_;
};

} // namespace strategy::after
