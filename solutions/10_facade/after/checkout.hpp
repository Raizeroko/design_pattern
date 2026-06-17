#pragma once

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

class CheckoutFacade {
public:
    std::string place_order(const std::string& sku, int cents) const {
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
