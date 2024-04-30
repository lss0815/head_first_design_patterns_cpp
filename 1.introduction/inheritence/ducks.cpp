#include <iostream>
#include <memory>

class Duck {
 public:
  virtual std::string display() = 0;
  virtual std::string quack() { return "quacking"; }
  virtual std::string swim() { return "swimming"; }
  // Newly added
  virtual std::string fly() { return "flying"; }
};

class MallardDuck : public Duck {
 public:
  std::string display() override { return "MallardDuck"; }
};

class RedheadDuck : public Duck {
 public:
  std::string display() override { return "RedheadDuck"; }
};

class RubberDuck : public Duck {
 public:
  std::string display() override { return "RubberDuck"; }
  std::string quack() override { return "squeaking"; }
  // Newly added
  std::string fly() override { return "doing nothing"; }
};

// Newly added
class DecoyDuck : public Duck {
 public:
  std::string display() override { return "DecoyDuck"; }
  std::string quack() override { return "doing nothing"; }
  std::string fly() override { return "doing nothing"; }
};

int main() {
  static const auto kShowDuck = [](std::shared_ptr<Duck> duck) {
    std::cout << duck->display() << ", " << duck->quack() << "\n";
    std::cout << duck->display() << ", " << duck->swim() << "\n";
    std::cout << duck->display() << ", " << duck->fly() << "\n";
  };

  std::shared_ptr<MallardDuck> mallard_duck = std::make_shared<MallardDuck>();
  std::shared_ptr<RedheadDuck> redhead_duck = std::make_shared<RedheadDuck>();
  std::shared_ptr<RubberDuck> rubber_duck = std::make_shared<RubberDuck>();
  std::shared_ptr<DecoyDuck> decoy_duck = std::make_shared<DecoyDuck>();

  kShowDuck(mallard_duck);
  kShowDuck(redhead_duck);
  kShowDuck(rubber_duck);
  kShowDuck(decoy_duck);

  return 0;
}