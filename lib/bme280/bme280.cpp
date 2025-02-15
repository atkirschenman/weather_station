#include "bme280.hpp"
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <Wire.h>
#include <cmath>
#include <string>
#include "Arduino.h"

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#include "esp_log.h"
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

static const char* TAG = "BME280";
std::string temperature_str = "temperature";
std::string humidity_str = "dew_point";
std::string pressure_str = "pressure";

BME280::BME280(std::string name, uint32_t interval) : SensorBase(name, interval)
{
    this->name = name;
}

void BME280::sensor_function()
{
    // initialize sensor
    if (!bme.begin(0x76)) // I2C
    {
        ESP_LOGE(TAG, "Could not find a valid BME280 sensor, check wiring!");
    }
    change_state(SensorDefines::State::READING_UNSTABLE);
    // Read sensor data
    while (Sensor.get_sensor_by_name(name).state != SensorDefines::State::SHUTTING_DOWN)
    {

        // If the sensor data is stable, change the state

        float temperature = bme.readTemperature();
        float humidity = bme.readHumidity();
        // Read sensor data
        float b = 17.62;
        float c = 243.12;
        float gamma = (b * temperature / (c + temperature)) + std::log(humidity / 100.0);
        float dewpoint = (c * gamma) / (b - gamma);

        Sensor.send_sensor_data(humidity_str, dewpoint);
        Sensor.send_sensor_data(temperature_str, bme.readTemperature());
        Sensor.send_sensor_data(pressure_str, bme.readPressure());
        change_state(SensorDefines::State::READING_STABLE);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    bme.setSampling(Adafruit_BME280::MODE_SLEEP);
    // Change the state to ready to sleep
    change_state(SensorDefines::State::READY_TO_SLEEP);
}

