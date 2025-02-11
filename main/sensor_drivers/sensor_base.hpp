#pragma once
#include "FreeRTOS.h"
#include "sensor_supervisor.hpp"
#include "sensor_defines.hpp"

/// @brief Sensors inherit this to communicate with sensor_supervisor
class SensorBase
{

    public:
        SensorBase(std::string name, Sensor::Type type, uint32_t interval);
    protected:
        virtual void sensor_function() = 0; 
        Sensor::Type sensor_type;    
        TaskHandle_t task;
    private:
        void main_sensor_task(void *params);
        std::thread sensor_thread;
};