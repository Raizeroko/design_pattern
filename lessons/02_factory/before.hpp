#pragma once

/*
场景：业务代码需要创建圆形、正方形等图形并通过统一接口计算面积。
新需求：图形种类和构造参数会继续增加。
当前问题：
1. 调用方必须知道 Circle、Square 等具体类型。
2. new 和构造参数散落在各个调用方，创建规则变化会引发多处修改。
3. 使用图形的业务代码与图形的创建细节耦合。
练习目标：集中对象创建规则，让调用方只描述“要什么”，不负责“怎么创建”。
*/

namespace factory::before {

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

} // namespace factory::before
