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

/*
模式角色与代码对照：
- [Product] Shape。
- [ConcreteProduct] Circle、Square。
- [创建请求] ShapeType + size。
- [Factory] ShapeFactory::create。
- [创建动作] switch 将请求映射成 make_unique<Circle/Square>。
*/

namespace factory::after {

// [Product / 抽象产品] 工厂统一返回 Shape。
struct Shape {
    virtual ~Shape() = default;
    virtual double area() const = 0;
};

// [ConcreteProduct 1] Circle 仍只负责圆形面积计算。
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

// [创建请求] ShapeType 让调用方描述“要哪种产品”。
enum class ShapeType {
    // [可选产品类型] 每个枚举值对应一个 ConcreteProduct。
    circle,
    square,
};

// [Factory / 工厂] 唯一知道具体产品及构造方式的角色。
class ShapeFactory {
public:
    // [创建入口] type 决定产品，size 提供当前简化场景的尺寸。
    static std::unique_ptr<Shape> create(ShapeType type, double size) {
        switch (type) {
        case ShapeType::circle:
            // [创建动作 1] 工厂把 circle 请求映射为 Circle(radius)。
            return std::make_unique<Circle>(size);
        case ShapeType::square:
            // [创建动作 2] 工厂把 square 请求映射为 Square(side)。
            return std::make_unique<Square>(size);
        }
        throw std::invalid_argument("unknown shape type");
    }
};

} // namespace factory::after
