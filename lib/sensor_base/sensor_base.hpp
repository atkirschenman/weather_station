#pragma once
#include <string>
#include <thread>
#include "sensor_defines.hpp"
/// @brief Sensors inherit this to communicate with sensor_supervisor
class SensorBase
{

  public:
    SensorBase(std::string name, uint32_t interval);
    virtual ~SensorBase() = default;

  protected:
    virtual void sensor_function() = 0;
    void change_state(SensorDefines::State state);

  private:
    uint32_t sensor_key;
    void main_sensor_task(void* params);
    std::thread sensor_thread;
    SensorDefines::Config sensor_config;
};