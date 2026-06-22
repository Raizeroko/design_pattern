#pragma once

#include <memory>

namespace factory::practice {

struct Shape {
    virtual ~Shape() = default;
    virtual double area() const = 0;
};

enum class ShapeType { circle, square };

class ShapeFactory {
public:
    static std::unique_ptr<Shape> create(ShapeType, double) {
        return nullptr; // TODO: create the requested concrete shape.
    }
};

} // namespace factory::practice

