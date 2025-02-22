#pragma once
#include <string>
#include "sensor_base.hpp"
/// @brief  this function needs to

class RainSensor : public SensorBase
{
  public:
    RainSensor(uint32_t interval);
    void sensor_function();
    void init();

  private:
    std::string name;
#ifdef ARDUINO
  private:
    static void IRAM_ATTR handleInterrupt();
#else
  public:
    void mock_handle_interupt(unsigned long time);
#endif
};