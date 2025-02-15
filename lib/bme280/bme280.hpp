#pragma once
#include <string>
#include "sensor_base.hpp"
class BME280 : public SensorBase
{
  public:
    BME280(std::string name, uint32_t interval);
    void sensor_function();

  private:
    std::string name;
};
