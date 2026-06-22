#pragma once

/*
参考重构：Facade
- InventoryService、PaymentService、ShippingService 保持各自职责。
- CheckoutFacade 用 place_order 表达一个高层业务用例，并隐藏固定编排顺序。
- 调用方只依赖门面，不必重复认识三个子系统。
真实系统中应显式处理支付失败、库存回滚等错误，门面不能吞掉失败信息。
*/

#include <string>

/*
模式角色与代码对照：
- [Subsystem] InventoryService、PaymentService、ShippingService。
- [Facade] CheckoutFacade。
- [统一入口] place_order。
- [内部编排动作] place_order 依次调用 inventory_、payment_、shipping_。
- [Client] after_test.cpp 只创建 Facade 并调用 place_order。
*/

namespace facade::after {

// [子系统 1] 库存服务只处理商品预留，不知道支付和物流。
class InventoryService {
public:
    std::string reserve(const std::string& sku) const { return "reserved:" + sku; }
};

// [子系统 2] 支付服务只处理扣款结果。
class PaymentService {
public:
    std::string charge(int cents) const { return cents > 0 ? "paid" : "rejected"; }
};

// [子系统 3] 物流服务只负责创建运单。
class ShippingService {
public:
    std::string create(const std::string& sku) const { return "shipment:" + sku; }
};

// [门面 / Facade] 对调用方暴露“下单”高层用例，对内保存子系统编排知识。
class CheckoutFacade {
public:
    // [统一入口] 页面、API 和批处理都只调用 place_order。
    std::string place_order(const std::string& sku, int cents) const {
        // [门面内部编排] 调用顺序只维护在这里，外部不再直接点名三个子系统。
        const auto stock = inventory_.reserve(sku);
        const auto payment = payment_.charge(cents);
        const auto shipment = shipping_.create(sku);
        return stock + "|" + payment + "|" + shipment;
    }

private:
    // [内部协作者] 三个子系统只在门面内部出现，不暴露给高层调用方。
    InventoryService inventory_;
    PaymentService payment_;
    ShippingService shipping_;
};

} // namespace facade::after
