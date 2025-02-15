#include "sensor_defines.hpp"
#include "esp_log.h"

static const char* TAG = "Sensor_Defines";
SensorDefines Sensor;

bool SensorDefines::send_sensor_data(std::string& name, float data)
{
    std::lock_guard<std::mutex> lock(data_mutex);
    // TODO: Check if sensor is registered
    // TODO: Check if sensor is in a stable state before accepting data
    data_map[name].second = data;
    return true;
}

float SensorDefines::get_sensor_data(std::string& name)
{
    std::lock_guard<std::mutex> lock(data_mutex);
    return data_map[name].second;
}

uint32_t SensorDefines::get_random_uint32()
{
    return (static_cast<uint32_t>(rand()) << 16) | static_cast<uint32_t>(rand());
}

uint32_t SensorDefines::register_sensor(Config sensor)
{
    std::srand(std::time(nullptr));
    std::lock_guard<std::mutex> lock(sensors_mutex);

    if (sensors_map.find(sensor.name) != sensors_map.end())
    {
        ESP_LOGE(TAG, "%s is already registered", sensor.name.c_str());
        return false;
    }
    ESP_LOGI(TAG, "%s has registered", sensor.name.c_str());
    sensors_map[sensor.name] = sensor;
    sensors_map[sensor.name].state = State::STARTING;
    return get_random_uint32();
}

SensorDefines::Config SensorDefines::get_sensor_by_name(std::string& name)
{
    std::lock_guard<std::mutex> lock(sensors_mutex);
    return sensors_map[name];
}

SensorDefines::Config SensorDefines::get_sensor_by_reading(std::string& reading)
{
    std::lock_guard<std::mutex> lock(data_mutex);
    return data_map[reading].first;
}

bool SensorDefines::change_state(uint32_t key, State state)
{
    std::lock_guard<std::mutex> lock(sensors_mutex);
    std::string name = sensor_keys_map[key];
    sensors_map[name].state = state;
    return true;
}