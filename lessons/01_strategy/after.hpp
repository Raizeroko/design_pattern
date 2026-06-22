#pragma once

/*
参考重构：Strategy
- ShippingStrategy 是稳定的算法边界，结账流程只依赖这个抽象。
- 每种配送算法独立封装；新增算法不需要修改已有算法。
- Checkout 通过 unique_ptr 拥有策略，明确生命周期并允许运行时替换实现。
注意：你的 practice 使用非拥有型裸指针也可以，但必须保证策略比 context 活得更久。
*/

#include <memory>
#include <utility>

namespace strategy::after {

// 稳定抽象：Checkout 不再关心具体计费公式。
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

// 上下文只负责使用策略，并通过 unique_ptr 明确拥有策略。
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
