#pragma once

#include <string>

namespace facade::before {

inline std::string reserve_stock(const std::string& sku) { return "reserved:" + sku; }
inline std::string charge(int cents) { return cents > 0 ? "paid" : "rejected"; }
inline std::string create_shipment(const std::string& sku) { return "shipment:" + sku; }

inline std::string checkout(const std::string& sku, int cents) {
    auto stock = reserve_stock(sku);
    auto payment = charge(cents);
    auto shipment = create_shipment(sku);
    return stock + "|" + payment + "|" + shipment;
}

} // namespace facade::before
