#pragma once

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

class DrinkDecorator : public Drink {
public:
    explicit DrinkDecorator(std::unique_ptr<Drink> inner) : inner_(std::move(inner)) {}

protected:
    const Drink& inner() const { return *inner_; }

private:
    std::unique_ptr<Drink> inner_;
};

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
