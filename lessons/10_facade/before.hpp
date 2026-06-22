#pragma once

/*
场景：一次结账需要依次协调库存、支付和物流子系统。
新需求：页面、批处理和 API 都要复用同一套下单流程。
当前问题：
1. 每个调用方都必须理解三个子系统及调用顺序。
2. 编排代码容易复制，任何流程变化都要修改多处。
3. 高层业务用例被底层子系统细节淹没。
练习目标：提供一个表达“下单”用例的简单入口，内部统一编排子系统。
*/

#include <string>

namespace facade::before {

// 库存子系统：为本次订单锁定商品。
inline std::string reserve_stock(const std::string& sku) { return "reserved:" + sku; }
// 支付子系统：根据金额返回支付结果。
inline std::string charge(int cents) { return cents > 0 ? "paid" : "rejected"; }
// 物流子系统：为已下单商品创建运单。
inline std::string create_shipment(const std::string& sku) { return "shipment:" + sku; }

// 每个页面、API 或批处理调用方都要亲自知道并重复这三步。
inline std::string checkout(const std::string& sku, int cents) {
    // 编排顺序暴露在调用方层面，子系统变化会影响所有入口。
    auto stock = reserve_stock(sku);
    auto payment = charge(cents);
    auto shipment = create_shipment(sku);
    return stock + "|" + payment + "|" + shipment;
}

} // namespace facade::before
