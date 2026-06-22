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

/*
模式角色与代码对照：
- [Component] Drink。
- [ConcreteComponent] Coffee。
- [Decorator] DrinkDecorator，内部持有另一个 Drink。
- [ConcreteDecorator] Milk、Syrup、OatMilk。
- [包装动作] 装饰器构造函数接收 inner。
- [叠加动作] inner().price/name + 当前加料的变化。
*/

namespace decorator::after {

// [Component] 点单和收银依赖的统一饮品接口。
struct Drink {
    virtual ~Drink() = default;
    virtual int price() const = 0;
    virtual std::string name() const = 0;
};

// [ConcreteComponent] 最内层基础咖啡，不包含加料。
struct Coffee final : Drink {
    int price() const override { return 12; }
    std::string name() const override { return "coffee"; }
};

// [Decorator] 保存另一个 Component，并为具体装饰器提供转发能力。
class DrinkDecorator : public Drink {
public:
    // [包装动作] 构造函数接收并保存被包装的 inner Drink。
    explicit DrinkDecorator(std::unique_ptr<Drink> inner) : inner_(std::move(inner)) {}

protected:
    // [委托动作] 具体装饰器通过 inner() 取得上一层结果。
    const Drink& inner() const { return *inner_; }

private:
    std::unique_ptr<Drink> inner_;
};

// [ConcreteDecorator 1] Milk 在内层结果上叠加牛奶职责。
class Milk final : public DrinkDecorator {
public:
    using DrinkDecorator::DrinkDecorator;
    // [叠加动作] 先调用 inner().price，再增加 3 元。
    int price() const override { return inner().price() + 3; }
    std::string name() const override { return inner().name() + "+milk"; }
};

class Syrup final : public DrinkDecorator {
public:
    using DrinkDecorator::DrinkDecorator;
    // [ConcreteDecorator 2] Syrup 独立叠加糖浆职责。
    int price() const override { return inner().price() + 2; }
    std::string name() const override { return inner().name() + "+syrup"; }
};

class OatMilk final : public DrinkDecorator {
public:
    using DrinkDecorator::DrinkDecorator;
    // [ConcreteDecorator 3] OatMilk 是新增职责，不修改已有类。
    int price() const override { return inner().price() + 5; }
    std::string name() const override { return inner().name() + "+oat"; }
};

} // namespace decorator::after
