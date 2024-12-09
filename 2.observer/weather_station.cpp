#include <iostream>
#include <memory>
#include <set>

class Observer {
 public:
  virtual void Update(float temp, float humidity, float pressure) = 0;
};

class Subject {
 public:
  virtual void RegisterObserver(Observer* observer) = 0;
  virtual void RemoveObserver(Observer* observer) = 0;
  virtual void NotifyObservers() = 0;
};

class DisplayElement {
 protected:
  virtual void Display() = 0;
};

class WeatherData : public Subject {
 public:
  WeatherData() = default;
  ~WeatherData() = default;

  void RegisterObserver(Observer* observer) override {
    observers_.insert(observer);
  }
  void RemoveObserver(Observer* observer) override {
    observers_.erase(observer);
  }

  void NotifyObservers() override {
    for (auto& observer : observers_) {
      observer->Update(temperature_, humidity_, pressure_);
    }
  }

  void MeasurementsChanged() { NotifyObservers(); }

  void SetMeasurements(float temperature, float humidity, float pressure) {
    temperature_ = temperature;
    humidity_ = humidity;
    pressure_ = pressure;
    MeasurementsChanged();
  }

 private:
  std::set<Observer*> observers_;
  float temperature_;
  float humidity_;
  float pressure_;
};

class CurrentConditionsDisplay : public Observer, public DisplayElement {
 public:
  CurrentConditionsDisplay(const std::shared_ptr<WeatherData> weather_data)
      : kWeatherData_(weather_data) {
    weather_data->RegisterObserver(this);
  }

  ~CurrentConditionsDisplay() {
    auto weather_data = kWeatherData_.lock();
    if (weather_data == nullptr) return;
    weather_data->RemoveObserver(this);
  }

  void Update(float temperature, float humidity, float pressure) override {
    temperature_ = temperature;
    humidity_ = humidity;
    Display();
  }

  void Display() {
    std::cout << "Current conditions: " << temperature_ << "F degrees and "
              << humidity_ << "\% humidity\n";
  }

 private:
  const std::weak_ptr<WeatherData> kWeatherData_;

  float temperature_{0.f};
  float humidity_{0.f};
};

int main() {
  auto weather_data = std::make_shared<WeatherData>();

  std::cout << "It's cloudy" << std::endl;
  weather_data->SetMeasurements(50.0, 60.0, 757.0);

  {
    CurrentConditionsDisplay current_conditions_display{weather_data};
    std::cout << "It's sunny" << std::endl;
    weather_data->SetMeasurements(60.0, 40.0, 762.0);
    std::cout << "It's rainy" << std::endl;
    weather_data->SetMeasurements(40.0, 90.0, 753.0);
  }

  std::cout << "It's sunny" << std::endl;
  weather_data->SetMeasurements(60.0, 40.0, 762.0);
  return 0;
}