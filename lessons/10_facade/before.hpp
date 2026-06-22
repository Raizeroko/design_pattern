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

/*
概念与代码对照：
- [Subsystem] reserve_stock、charge、create_shipment。
- [Client / 调用方] before_test.cpp 模拟页面或 API。
- [编排动作] 调用方依次调用三个子系统并组合结果。
- [问题证据] 调用方直接出现三个子系统名称和调用顺序。
*/

namespace facade::before {

// [子系统 1] 库存模块：为本次订单锁定商品。
inline std::string reserve_stock(const std::string& sku) { return "reserved:" + sku; }
// [子系统 2] 支付模块：根据金额返回支付结果。
inline std::string charge(int cents) { return cents > 0 ? "paid" : "rejected"; }
// [子系统 3] 物流模块：为已下单商品创建运单。
inline std::string create_shipment(const std::string& sku) { return "shipment:" + sku; }

// [缺少 Facade] before 没有统一的高层入口。
// [问题证据-位置] 三个函数的调用顺序直接展示在 before_test.cpp。
// [变化影响] 页面、API、批处理都会复制编排并直接依赖三个子系统。

} // namespace facade::before
