#pragma once

#include <memory>
#include <string>
#include <utility>

namespace decorator::practice {

struct Drink {
    virtual ~Drink() = default;
    virtual int price() const = 0;
    virtual std::string name() const = 0;
};

struct Coffee final : Drink {
    int price() const override { return 12; }
    std::string name() const override { return "coffee"; }
};

class Milk final : public Drink {
public:
    explicit Milk(std::unique_ptr<Drink> inner) : inner_(std::move(inner)) {}
    int price() const override { return inner_->price(); /* TODO: add milk price. */ }
    std::string name() const override { return inner_->name(); /* TODO */ }

private:
    std::unique_ptr<Drink> inner_;
};

class OatMilk final : public Drink {
public:
    explicit OatMilk(std::unique_ptr<Drink> inner) : inner_(std::move(inner)) {}
    int price() const override { return inner_->price(); /* TODO: add oat milk price. */ }
    std::string name() const override { return inner_->name(); /* TODO */ }

private:
    std::unique_ptr<Drink> inner_;
};

} // namespace decorator::practice

