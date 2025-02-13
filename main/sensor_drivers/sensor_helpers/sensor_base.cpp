#include "sensor_base.hpp"
#include <chrono>
#include <functional>
#include "esp_log.h"
static const char* TAG = "Sensor";

SensorBase::SensorBase(std::string name, uint32_t interval)
    : sensor_thread([this] { main_sensor_task(this); })
{
    sensor_config.name = name;
    sensor_config.interval = interval;
    sensor_config.state = SensorDefines::State::UNREGISTERED;
}

void SensorBase::main_sensor_task(void* params)
{
    SensorBase* sensor = (SensorBase*)params;

    sensor->sensor_key = Sensor.register_sensor(sensor->sensor_config);

    bool is_registered = false;
    while (Sensor.get_sensor_by_name(sensor->sensor_config.name).state !=
           SensorDefines::State::STARTING)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ESP_LOGI(TAG, "Waiting for sensor to start...");
    }

    sensor->sensor_function();
}

void SensorBase::change_state(SensorDefines::State state)
{
    Sensor.change_state(sensor_key, state);
}