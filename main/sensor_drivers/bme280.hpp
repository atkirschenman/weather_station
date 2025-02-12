#pragma once
#include "sensor_base.hpp"

class BME280 : public SensorBase
{
  public:
    BME280(std::string name, SensorDefines::Type type, uint32_t interval);
    ~BME280();
    void sensor_function();
};
