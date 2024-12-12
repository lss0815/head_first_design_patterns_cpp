#include <iostream>
#include <memory>
#include <string>

class Coffee {
 public:
  virtual std::string GetDescription() = 0;
  virtual double GetCost() = 0;

 protected:
  double cost_{0};
};

class CoffeeTopping : public Coffee {
 public:
  explicit CoffeeTopping(std::shared_ptr<Coffee> base_coffee)
      : base_coffee_(base_coffee) {}
  std::string GetDescription() override {
    return base_coffee_->GetDescription() + ", " + topping_name_ + ": " +
           std::to_string(topping_cost_);
  }
  double GetCost() override { return base_coffee_->GetCost() + topping_cost_; }

 protected:
  std::shared_ptr<Coffee> base_coffee_;
  std::string topping_name_;
  double topping_cost_;
};

class Espresso : public Coffee {
 public:
  Espresso() { cost_ = 100.0; }

  std::string GetDescription() override {
    return "Espresso: " + std::to_string(cost_);
  }

  double GetCost() override { return cost_; }
};

class Whipping : public CoffeeTopping {
 public:
  Whipping(std::shared_ptr<Coffee> base_coffee) : CoffeeTopping(base_coffee) {
    topping_name_ = "whipping";
    topping_cost_ = 10.0;
  }
};

class ChocoChip : public CoffeeTopping {
 public:
  ChocoChip(std::shared_ptr<Coffee> base_coffee) : CoffeeTopping(base_coffee) {}
  std::string GetDescription() override {
    return base_coffee_->GetDescription() +
           ", ChocoChip: originally 20.0 but discounted to 5.0";
  }
  double GetCost() override { return base_coffee_->GetCost() + 5.0; }
};

int main() {
  std::shared_ptr<Coffee> order =
      std::make_shared<ChocoChip>(std::make_shared<Whipping>(
          std::make_shared<Whipping>(std::make_shared<Espresso>())));
  std::cout << order->GetDescription() << std::endl;
  std::cout << "Total cost: " << order->GetCost() << std::endl;
  return 0;
}