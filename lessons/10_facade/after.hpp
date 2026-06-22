#pragma once

/*
参考重构：Facade
- InventoryService、PaymentService、ShippingService 保持各自职责。
- CheckoutFacade 用 place_order 表达一个高层业务用例，并隐藏固定编排顺序。
- 调用方只依赖门面，不必重复认识三个子系统。
真实系统中应显式处理支付失败、库存回滚等错误，门面不能吞掉失败信息。
*/

#include <string>

namespace facade::after {

class InventoryService {
public:
    std::string reserve(const std::string& sku) const { return "reserved:" + sku; }
};

class PaymentService {
public:
    std::string charge(int cents) const { return cents > 0 ? "paid" : "rejected"; }
};

class ShippingService {
public:
    std::string create(const std::string& sku) const { return "shipment:" + sku; }
};

// 门面对外暴露高层用例，对内保存子系统编排知识。
class CheckoutFacade {
public:
    std::string place_order(const std::string& sku, int cents) const {
        // 调用顺序只维护在这里，页面或 API 调用方无需重复编排。
        const auto stock = inventory_.reserve(sku);
        const auto payment = payment_.charge(cents);
        const auto shipment = shipping_.create(sku);
        return stock + "|" + payment + "|" + shipment;
    }

private:
    InventoryService inventory_;
    PaymentService payment_;
    ShippingService shipping_;
};

} // namespace facade::after
