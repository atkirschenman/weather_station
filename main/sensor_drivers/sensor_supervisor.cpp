#include "sensor_supervisor.hpp"
#include "sensor_defines.hpp"
#include "esp_log.h"

const char *TAG = "SensorSupervisor";

SensorSupervisor::SensorSupervisor()
{
    sensor_thread = std::thread(&SensorSupervisor::registerSensor, this);
}


SensorSupervisor::~SensorSupervisor()
{
}

bool SensorSupervisor::registerSensor(std::shared_ptr<Sensor::Config> sensor)
{
    for(;;)
    {
        std::unique_lock<std::mutex> lock(Sensor::sensor_queue_mutex);
        Sensor::cv.wait(lock, [] { return !Sensor::sensor_queue.empty(); });
        ESP_LOGI(TAG, "Registering sensor %s", Sensor::sensor_queue.front()->name.c_str());
        sensors.emplace_back(Sensor::sensor_queue.front());
        Sensor::sensor_queue.front()->state = Sensor::State::STARTING;
        Sensor::sensor_queue.pop();
        
    }
}