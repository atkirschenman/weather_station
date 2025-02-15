#pragma once
#include <memory>
#include <mutex>
#include <thread>
#include <vector>
#include "sensor_defines.hpp"
/// @brief Sensor Supervisor gathers data readings, coordinating sleep cycles and verifying data
/// validity
///
class SensorSupervisor
{
  public:
    /// @brief Constructor
    SensorSupervisor();
    /// @brief Destructor
    ~SensorSupervisor();

  private:
    /// @brief Initialize the sensor supervisor
    void init();
    /// @brief Run the sensor supervisor
    void run();
    /// @brief Sensor supervisor thread
    std::thread sensor_thread;
};

// encoder - 500 ms

// rotary resistor - every 15 seconds?

// temperature / humidity - every 15 seconds

// rain fall - on interupt

//