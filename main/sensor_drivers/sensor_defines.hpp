#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace Sensor
{
    enum class State
    {
        UNREGISTERED,
        STARTING,
        READING_UNSTABLE,
        READING_STABLE,
        READING_ERROR,
        READY_TO_SLEEP,
    };

    enum class Type 
    {
        TEMPERATURE,
        HUMIDITY,
        PRESSURE,
        LIGHT,
        RAINFALL,
        WIND_SPEED,
        WIND_DIRECTION,
    };

    struct Config
    {
        std::string name;
        Type type;
        State state;
        uint32_t interval;
    };

    extern std::queue<std::shared_ptr<Config>> sensor_queue;
    extern std::mutex sensor_queue_mutex;
    extern std::condition_variable cv;
}