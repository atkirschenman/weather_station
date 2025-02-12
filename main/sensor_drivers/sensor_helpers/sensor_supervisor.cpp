#include "sensor_supervisor.hpp"
#include "esp_log.h"
#include "sensor_defines.hpp"

const char* TAG = "SensorSupervisor";

SensorSupervisor::SensorSupervisor()
{
    sensor_thread = std::thread(&SensorSupervisor::registerSensor, this);
}

SensorSupervisor::~SensorSupervisor()
{
}
