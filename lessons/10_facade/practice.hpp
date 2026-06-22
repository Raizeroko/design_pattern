#pragma once

#include <string>

namespace facade::practice {

class CheckoutFacade {
public:
    std::string place_order(const std::string&, int) const {
        return {}; // TODO: coordinate inventory, payment, and shipping.
    }
};

} // namespace facade::practice

