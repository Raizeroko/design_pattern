#pragma once

/*
参考重构：Simple Factory
- Shape 保持调用方使用对象时的统一接口。
- ShapeType 表达创建意图，避免用容易拼错的字符串。
- ShapeFactory 集中具体类型与构造规则；调用方不再直接 new Circle/Square。
代价：新增图形仍需修改工厂的 switch，图形特别多时可继续演进为注册式工厂。
*/

#include <memory>
#include <stdexcept>

namespace factory::after {

struct Shape {
    virtual ~Shape() = default;
    virtual double area() const = 0;
};

struct Circle final : Shape {
    explicit Circle(double radius) : radius_(radius) {}

    double area() const override { return 3.14 * radius_ * radius_; }

private:
    double radius_;
};

struct Square final : Shape {
    explicit Square(double side) : side_(side) {}

    double area() const override { return side_ * side_; }

private:
    double side_;
};

// 创建意图是强类型枚举，调用方不会传入任意字符串。
enum class ShapeType {
    circle,
    square,
};

// 唯一知道具体类型构造方式的地方。
class ShapeFactory {
public:
    static std::unique_ptr<Shape> create(ShapeType type, double size) {
        switch (type) {
        case ShapeType::circle:
            return std::make_unique<Circle>(size);
        case ShapeType::square:
            return std::make_unique<Square>(size);
        }
        throw std::invalid_argument("unknown shape type");
    }
};

} // namespace factory::after
