#pragma once

#include <stdexcept>
#include <string>

namespace strategy::before {

inline int shipping_fee(const std::string& method, int distance_km, bool vip) {
    if (method == "standard") {
        return vip ? distance_km * 2 : 10 + distance_km * 2;
    }
    if (method == "express") {
        return vip ? distance_km * 4 : 20 + distance_km * 4;
    }
    throw std::invalid_argument("unknown shipping method");
}

} // namespace strategy::before
