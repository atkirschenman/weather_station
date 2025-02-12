#pragma once
#include <condition_variable>
#include <cstdint>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <unordered_map>

class SensorDefines
{
  public:
    enum class State
    {
        UNREGISTERED,
        STARTING,
        READING_UNSTABLE,
        READING_STABLE,
        READING_ERROR,
        SHUTTING_DOWN,
    };

    struct Config
    {
        std::string name;
        State state;
        uint32_t interval;
    };

    bool sendSensorData(std::string& name, float data);
    float getSensorData(std::string& name);

    bool registerSensor(Config sensor);
    Config get_sensor_by_name(std::string& name);
    Config get_sensor_by_reading(std::string& reading);
    bool change_state(uint32_t key, State state);

  private:
    uint32_t get_random_uint32();

  private:
    /// @brief Mutex for sensor supervisor
    std::mutex data_mutex;
    /// @brief List of data readings
    std::unordered_map<std::string, std::pair<Config, float>> data;
    /// @brief Mutex for sensor supervisor
    std::mutex sensors_mutex;
    /// @brief List of sensors
    std::unordered_map<std::string, std::shared_ptr<SensorDefines::Config>> sensors;

    std::unordered_map<std::string, uint32_t> sensor_keys;
    std::mutex keys_mutex;

    std::condition_variable cv;
};

extern SensorDefines Sensor; // Global instance declaration