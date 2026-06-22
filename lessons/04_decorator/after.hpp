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

// 点单和收银只依赖 Drink：任何组合都能给出价格和小票名称。
struct Drink {
    virtual ~Drink() = default;
    virtual int price() const = 0;
    virtual std::string name() const = 0;
};

// Coffee 是最内层的基础饮品，不包含任何加料。
struct Coffee final : Drink {
    int price() const override { return 12; }
    std::string name() const override { return "coffee"; }
};

// 公共装饰器保存内层对象，具体装饰器只负责叠加自己的变化。
class DrinkDecorator : public Drink {
public:
    // 每一层加料接管内层饮品的所有权，形成一条完整组合链。
    explicit DrinkDecorator(std::unique_ptr<Drink> inner) : inner_(std::move(inner)) {}

protected:
    // 具体加料先取得内层结果，再叠加自己的价格或名称。
    const Drink& inner() const { return *inner_; }

private:
    std::unique_ptr<Drink> inner_;
};

// Milk 与其他装饰器保持相同接口，因此可以继续被下一层包装。
class Milk final : public DrinkDecorator {
public:
    using DrinkDecorator::DrinkDecorator;
    // 牛奶只知道自己加 3 元、在小票追加 +milk。
    int price() const override { return inner().price() + 3; }
    std::string name() const override { return inner().name() + "+milk"; }
};

class Syrup final : public DrinkDecorator {
public:
    using DrinkDecorator::DrinkDecorator;
    // 糖浆与牛奶互不依赖，可以单独使用或任意组合。
    int price() const override { return inner().price() + 2; }
    std::string name() const override { return inner().name() + "+syrup"; }
};

class OatMilk final : public DrinkDecorator {
public:
    using DrinkDecorator::DrinkDecorator;
    // 新增燕麦奶没有改动 Coffee、Milk 或点单流程。
    int price() const override { return inner().price() + 5; }
    std::string name() const override { return inner().name() + "+oat"; }
};

} // namespace decorator::after
