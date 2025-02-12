#include "sensor_base.hpp"
#include <chrono>
#include "esp_log.h"
const char* TAG = "Sensor";

SensorBase::SensorBase(std::string name, Sensor::Type type, uint32_t interval)
{
    sensor_config.name = name;
    sensor_config.type = type;
    sensor_config.interval = interval;
    sensor_config.state = Sensor.State::UNREGISTERED;
    std::thread = std::thread(&SensorBase::main_sensor_task, this);
}

void SensorBase::main_sensor_task(void* params)
{
    SensorBase* sensor = (SensorBase*)params;

    sensor->sensor_key = Sensor.registerSensor(sensor->sensor_config);

    bool is_registered = false;
    while (Sensor.get_sensor_by_name(sensor->sensor_config.name).state != Sensor.State::STARTING)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        log_i(TAG, "Waiting for sensor to start...");
    }

    sensor->sensor_function();
}

void SensorBase::change_state(Sensor::State state)
{
    Sensor.change_state(sensor_key, state);
}