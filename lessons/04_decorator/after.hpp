#pragma once

/*
参考重构：Decorator
- Drink 是基础对象与所有装饰器共同遵守的接口。
- DrinkDecorator 持有并转发给被包装对象，统一表达“包一层”的关系。
- Milk、Syrup、OatMilk 只叠加自己的价格和描述，可按任意顺序运行时组合。
unique_ptr 明确每层装饰器拥有内层对象，组合销毁时不会泄漏。
*/

#include <memory>
#include <string>
#include <utility>

namespace decorator::after {

struct Drink {
    virtual ~Drink() = default;
    virtual int price() const = 0;
    virtual std::string name() const = 0;
};

struct Coffee final : Drink {
    int price() const override { return 12; }
    std::string name() const override { return "coffee"; }
};

// 公共装饰器保存内层对象，具体装饰器只负责叠加自己的变化。
class DrinkDecorator : public Drink {
public:
    explicit DrinkDecorator(std::unique_ptr<Drink> inner) : inner_(std::move(inner)) {}

protected:
    const Drink& inner() const { return *inner_; }

private:
    std::unique_ptr<Drink> inner_;
};

// Milk 与其他装饰器保持相同接口，因此可以继续被下一层包装。
class Milk final : public DrinkDecorator {
public:
    using DrinkDecorator::DrinkDecorator;
    int price() const override { return inner().price() + 3; }
    std::string name() const override { return inner().name() + "+milk"; }
};

class Syrup final : public DrinkDecorator {
public:
    using DrinkDecorator::DrinkDecorator;
    int price() const override { return inner().price() + 2; }
    std::string name() const override { return inner().name() + "+syrup"; }
};

class OatMilk final : public DrinkDecorator {
public:
    using DrinkDecorator::DrinkDecorator;
    int price() const override { return inner().price() + 5; }
    std::string name() const override { return inner().name() + "+oat"; }
};

} // namespace decorator::after
