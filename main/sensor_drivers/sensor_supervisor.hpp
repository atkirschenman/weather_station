#pragma once
#include "sensor_defines.hpp"
#include <vector>
#include <memory>
#include <mutex>
#include <thread>
/// @brief Sensor Supervisor gathers data readings, coordinating sleep cycles and verifying data validity
///
class SensorSupervisor
{
    public:
        /// @brief Constructor
        SensorSupervisor();
        /// @brief Destructor
        ~SensorSupervisor();
        /// @brief Register a sensor to the supervisor
        bool registerSensor(std::shared_ptr<Sensor::Config> sensor);
        
    private:
        /// @brief Initialize the sensor supervisor
        void init();
        /// @brief Run the sensor supervisor
        void run();
        /// @brief Mutex for sensor supervisor
        std::mutex sensor_mutex;
        /// @brief List of sensors
        std::vector<std::shared_ptr<Sensor::Config>> sensors;
        /// @brief Sensor supervisor thread
        std::thread sensor_thread;
};


//encoder - 500 ms 

//rotary resistor - every 15 seconds? 

// temperature / humidity - every 15 seconds

// rain fall - on interupt

//