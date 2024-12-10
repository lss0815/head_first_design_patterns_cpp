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

class Espresso : public Coffee {
 public:
  Espresso() { cost_ = 100.0; }

  std::string GetDescription() override {
    return "Espresso: " + std::to_string(cost_) + ", ";
  }

  double GetCost() override { return cost_; }
};

class CoffeeTopping : public Coffee {
 public:
  CoffeeTopping(std::shared_ptr<Coffee> coffee) {}
};

int main() {
  Espresso order;
  std::cout << order.GetDescription() << std::endl;
  std::cout << "Total cost: " << order.GetCost() << std::endl;
  return 0;
}