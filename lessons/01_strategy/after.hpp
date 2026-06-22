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
    // 所有配送产品接受相同业务输入，Checkout 因此可以统一调用。
    virtual int fee(int distance_km, bool vip) const = 0;
};

// 标准配送产品只保存自己的计费知识。
struct StandardShipping final : ShippingStrategy {
    int fee(int distance_km, bool vip) const override {
        return (vip ? 0 : 10) + distance_km * 2;
    }
};

// 加急配送产品独立演进，不影响标准配送公式。
struct ExpressShipping final : ShippingStrategy {
    int fee(int distance_km, bool vip) const override {
        return (vip ? 0 : 20) + distance_km * 4;
    }
};

// 新增“当日达”只增加一个策略类，无需进入 Checkout 添加分支。
struct SameDayShipping final : ShippingStrategy {
    int fee(int distance_km, bool vip) const override {
        return (vip ? 15 : 35) + distance_km * 6;
    }
};

// 上下文只负责使用策略，并通过 unique_ptr 明确拥有策略。
class Checkout {
public:
    // 创建结账上下文时选择本次订单使用的配送产品。
    explicit Checkout(std::unique_ptr<ShippingStrategy> strategy)
        : strategy_(std::move(strategy)) {}

    int shipping_fee(int distance_km, bool vip) const {
        // 结账流程只转交业务参数，不知道公式细节。
        return strategy_->fee(distance_km, vip);
    }

private:
    // Checkout 拥有策略，保证计算期间策略对象始终有效。
    std::unique_ptr<ShippingStrategy> strategy_;
};

} // namespace strategy::after
