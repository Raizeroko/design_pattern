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

// 工厂返回统一的 Shape，后续计算面积的业务代码不依赖具体图形。
struct Shape {
    virtual ~Shape() = default;
    virtual double area() const = 0;
};

// 具体图形仍负责各自领域计算；工厂不会接管对象行为。
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
    // 这些值是调用方向工厂表达的创建需求。
    circle,
    square,
};

// 唯一知道具体类型构造方式的地方。
class ShapeFactory {
public:
    // size 在本场景表示半径或边长；真实项目可改为专用参数对象。
    static std::unique_ptr<Shape> create(ShapeType type, double size) {
        switch (type) {
        case ShapeType::circle:
            // 只有工厂知道 circle 应映射为 Circle(radius)。
            return std::make_unique<Circle>(size);
        case ShapeType::square:
            // 构造校验或默认值也可以集中维护在创建分支中。
            return std::make_unique<Square>(size);
        }
        throw std::invalid_argument("unknown shape type");
    }
};

} // namespace factory::after
