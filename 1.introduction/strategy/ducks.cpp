#include <iostream>
#include <memory>

class QuackBehavior {
 public:
  virtual std::string Quack() = 0;
};

class QuackingQuackBehavior : public QuackBehavior {
 public:
  std::string Quack() override { return "quacking"; }
};

class SqueakingQuackBehavior : public QuackBehavior {
 public:
  std::string Quack() override { return "squeaking"; }
};

class DoingNothingQuackBehavior : public QuackBehavior {
 public:
  std::string Quack() override { return "doing nothing"; }
};

class FlyBehavior {
 public:
  virtual std::string Fly() = 0;
};

class FlyingFlyBehavior : public FlyBehavior {
 public:
  std::string Fly() override { return "flying"; }
};

class DoingNothingFlyBehavior : public FlyBehavior {
 public:
  std::string Fly() override { return "doing nothing"; }
};

class Duck {
 public:
  Duck() {
    fly_behavior_ = std::make_shared<FlyingFlyBehavior>();
    quack_behavior_ = std::make_shared<QuackingQuackBehavior>();
  }

  virtual std::string Display() = 0;
  virtual std::string Swim() { return "swimming"; }

  std::string Quack() { return quack_behavior_->Quack(); }

  std::string Fly() { return fly_behavior_->Fly(); }

 protected:
  std::shared_ptr<QuackBehavior> quack_behavior_;
  std::shared_ptr<FlyBehavior> fly_behavior_;
};

class MallardDuck : public Duck {
 public:
  MallardDuck() = default;
  std::string Display() override { return "MallardDuck"; }
};

class RedheadDuck : public Duck {
 public:
  RedheadDuck() = default;
  std::string Display() override { return "RedheadDuck"; }
};

class RubberDuck : public Duck {
 public:
  RubberDuck() {
    fly_behavior_ = std::make_shared<DoingNothingFlyBehavior>();
    quack_behavior_ = std::make_shared<SqueakingQuackBehavior>();
  }

  std::string Display() override { return "RubberDuck"; }
};

class DecoyDuck : public Duck {
 public:
  DecoyDuck() {
    fly_behavior_ = std::make_shared<DoingNothingFlyBehavior>();
    quack_behavior_ = std::make_shared<DoingNothingQuackBehavior>();
  }

  std::string Display() override { return "DecoyDuck"; }
};

int main() {
  static const auto kShowDuck = [](std::shared_ptr<Duck> duck) {
    std::cout << duck->Display() << ", " << duck->Quack() << "\n";
    std::cout << duck->Display() << ", " << duck->Swim() << "\n";
    std::cout << duck->Display() << ", " << duck->Fly() << "\n";
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