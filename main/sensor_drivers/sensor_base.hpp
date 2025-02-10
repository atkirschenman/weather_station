#pragma once
#include "FreeRTOS.h"
/// @brief Sensors inherit this to communicate with sensor_supervisor
class SensorBase
{

    public:
        SensorBase();
    protected:
        virtual void sensor_function() = 0; 

    private:
            
        TaskHandle_t task;
        static void main_sensor_task(void *pvParameters);

    

};