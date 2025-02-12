#include "sensor_defines.hpp"
#include "esp_log.h"

const char* TAG = "Sensor_Defines";
SensorDefines Sensor;

bool SensorDefines::sendSensorData(std::string name, float data)
{
    std::lock_guard<std::mutex> lock(data_mutex);
    data[name] = data;
    return true;
}

float SensorDefines::getSensorData(std::string name)
{
    std::lock_guard<std::mutex> lock(data_mutex);
    return data[name];
}

uint32_t get_random_uint32()
{
    return (static_cast<uint32_t>(rand()) << 16) | static_cast<uint32_t>(rand());
}

uint32_t SensorDefines::registerSensor(Config sensor)
{
    std::srand(std::time(nullptr));
    std::lock_guard<std::mutex> lock(sensors_mutex);

    if (sensors.find(sensor->name) != sensors.end())
    {
        log_e(TAG, "%s is already registered", sensor->name.c_str());
        return false;
    }
    log_i(TAG, "%s has registered", sensor->name.c_str());
    sensors[sensor->name] = sensor;
    sensors[sensor->name]->state = State::STARTING;
    return get_random_uint32();
}

Config SensorDefines::get_sensor_by_name(std::string name)
{
    std::lock_guard<std::mutex> lock(sensors_mutex);
    return sensors[name];
}

Config SensorDefines::get_sensor_by_reading(std::string reading)
{
    std::lock_guard<std::mutex> lock(data_mutex);
    return data[reading].first;
}

bool SensorDefines::change_state(uint32_t key, State state)
{
    std::lock_guard<std::mutex> lock(sensors_mutex);
    std::string name = sensor_keys[key];
    sensors[name]->state = state;
    return true;
}