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
        READY_TO_SLEEP,
        SHUTTING_DOWN,
    };

    struct Config
    {
        std::string name;
        State state;
        uint32_t interval;
    };

    bool send_sensor_data(std::string& name, float data);
    float get_sensor_data(std::string& name);

    uint32_t register_sensor(Config sensor);
    Config get_sensor_by_name(std::string& name);
    Config get_sensor_by_reading(std::string& reading);
    bool change_state(uint32_t key, State state);

  private:
    uint32_t get_random_uint32();

  private:
    /// @brief Mutex for sensor supervisor
    std::mutex data_mutex;
    /// @brief List of data readings
    std::unordered_map<std::string, std::pair<Config, float>> data_map;
    /// @brief Mutex for sensor supervisor
    std::mutex sensors_mutex;
    /// @brief List of sensors
    std::unordered_map<std::string, Config> sensors_map;

    std::unordered_map<uint32_t, std::string> sensor_keys_map;
    std::mutex keys_mutex;

    std::condition_variable cv;
};

extern SensorDefines Sensor; // Global instance declaration