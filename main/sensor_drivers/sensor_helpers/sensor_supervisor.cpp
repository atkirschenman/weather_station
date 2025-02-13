#include "sensor_supervisor.hpp"
#include "esp_log.h"
#include "sensor_defines.hpp"

static const char* TAG = "SensorSupervisor";

SensorSupervisor::SensorSupervisor()
{
    ESP_LOGI(TAG, "Sensor Supervisor Started");
}

SensorSupervisor::~SensorSupervisor()
{
}
