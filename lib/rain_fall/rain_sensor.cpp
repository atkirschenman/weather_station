#include "rain_sensor.hpp"
#include <atomic>
#include "Arduino.h"

std::atomic<bool> rainfall_flag;

RainSensor::RainSensor(uint32_t interval) : SensorBase("rain_sensor", interval)
{
    this->name = name;
}

void RainSensor::sensor_function()
{
    // initialize sensor
    // Read sensor data
    while (Sensor.get_sensor_by_name(name).state != SensorDefines::State::SHUTTING_DOWN)
    {
        // If the sensor data is stable, change the state
        change_state(SensorDefines::State::READING_STABLE);
    }
}

void RainSensor::interrupt_handler()
{
    // Check if the interrupt was triggered by the rain sensor
    if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0)
    {
        // Call the function to handle the interrupt
        rainfall_flag = true;
    }
}

void RainSensor::init()
{
    // Configure GPIO pin for rain sensor
    pinMode(RAIN_SENSOR_PIN, INPUT_PULLUP);

    // Enable wake-up from this GPIO pin
    esp_sleep_enable_ext0_wakeup(RAIN_SENSOR_PIN, 1); // 1 = HIGH level trigger

    // Attach interrupt
    attachInterrupt(digitalPinToInterrupt(RAIN_SENSOR_PIN),
                    std::bind(&RainSensor::interrupt_handler, this), RISING);
}
