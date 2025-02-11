#include "sensor_base.hpp"
#include "esp_log.h"

const char* TAG = "Sensor";

SensorBase(std::string name, Sensor::Type type, uint32_t interval)
{
    sensor_type = type;
    sensor_config.name = name;
    sensor_config.type = type;
    sensor_config.interval = interval;
    sensor_config.state = Sensor::State::UNREGISTERED;
    std::thread = std::thread(&SensorBase::main_sensor_task, this);
}

void SensorBase::main_sensor_task(void* params)
{
    SensorBase* sensor = (SensorBase*)params;
    {
        std::lock_guard<std::mutex> lock(Sensor::sensor_queue_mutex);
        ESP_LOGI(TAG, "%s is requesting registration", sensor->sensor_config.name.c_str());
        Sensor::sensor_queue.push(std::make_shared<Sensor::Config>(sensor->sensor_config));
    }
    Sensor::cv.notify_one();
    sensor->sensor_function();
    xtaskDelete(NULL);
}