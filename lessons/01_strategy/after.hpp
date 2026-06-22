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

/*
模式角色与代码对照：
- [Strategy] ShippingStrategy::fee。
- [ConcreteStrategy] StandardShipping、ExpressShipping、SameDayShipping。
- [Context] Checkout。
- [注入动作] Checkout 构造函数接收策略。
- [委托动作] Checkout::shipping_fee 调用 strategy_->fee。
*/

namespace strategy::after {

// [Strategy / 策略接口] Checkout 只认识这个统一计费动作。
struct ShippingStrategy {
    virtual ~ShippingStrategy() = default;
    // [策略动作] 所有具体策略都必须实现 fee。
    virtual int fee(int distance_km, bool vip) const = 0;
};

// [ConcreteStrategy 1] 封装标准配送公式。
struct StandardShipping final : ShippingStrategy {
    int fee(int distance_km, bool vip) const override {
        return (vip ? 0 : 10) + distance_km * 2;
    }
};

// [ConcreteStrategy 2] 封装加急配送公式。
struct ExpressShipping final : ShippingStrategy {
    int fee(int distance_km, bool vip) const override {
        return (vip ? 0 : 20) + distance_km * 4;
    }
};

// [ConcreteStrategy 3] 新增当日达时只增加本类，不修改 Context。
struct SameDayShipping final : ShippingStrategy {
    int fee(int distance_km, bool vip) const override {
        return (vip ? 15 : 35) + distance_km * 6;
    }
};

// [Context / 上下文] 结账流程保存并使用当前订单选择的策略。
class Checkout {
public:
    // [注入动作] 构造 Checkout 时把具体策略交给上下文。
    explicit Checkout(std::unique_ptr<ShippingStrategy> strategy)
        : strategy_(std::move(strategy)) {}

    int shipping_fee(int distance_km, bool vip) const {
        // [委托动作] Context 把计算请求转给 Strategy::fee。
        return strategy_->fee(distance_km, vip);
    }

private:
    // [Context 与 Strategy 的关系] Checkout 独占当前策略的生命周期。
    std::unique_ptr<ShippingStrategy> strategy_;
};

} // namespace strategy::after
