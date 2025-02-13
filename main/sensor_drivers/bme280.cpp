#include "bme280.hpp"
#include "CPPSPI/cppspi.h"
#include "bme280_spi/bme280_spi.h"
#include "esp_log.h"

static const char* TAG = "BME280";
CPPSPI::Spi spi3;
constexpr static int SPI_3_MISO = 19;
constexpr static int SPI_3_MOSI = 23;
constexpr static int SPI_3_SCLK = 18;
constexpr static int BME280_SS_PIN = 5;

BME280::BME280(std::string name, Sensor::Type type, uint32_t interval)
    : SensorBase(name, type, interval)
{
}

BME280::~BME280()
{
}

void BME280::sensor_function()
{
    // initialize sensor
    CPPBME280::BME280SPI bme280spi;
    spi3.Init(SPI3_HOST, SPI_3_MISO, SPI_3_MOSI, SPI_3_SCLK);

    bme280spi.InitSpi(&spi3, BME280_SS_PIN);

    bme280spi.Init();
    bme280spi.SetMode(1);
    bme280spi.SetConfigFilter(1);

    change_state(Sensor::State::READING_UNSTABLE);
    float temp[3] = {0};
    float hum[3] = {0};
    float press[3] = {0};
    int i = 0;
    // Read sensor data
    while (Sensor.get_sensor_by_name(sensor_config.name).state != Sensor.State::SHUTTING_DOWN)
    {
        bool stable = true;
        // Check if the sensor data is stable
        if (temp[0] != temp[1] || temp[0] != temp[2])
        {
            stable = false;
        }
        if (hum[0] != hum[1] || hum[0] != hum[2])
        {
            stable = false;
        }
        if (press[0] != press[1] || press[0] != press[2])
        {
            stable = false;
        }

        // If the sensor data is stable, change the state
        if (stable)
        {
            change_state(Sensor::State::READING_STABLE);
        }

        // Read sensor data
        bme280spi.GetAllResults(&temp[i % 3], &hum[i % 3], &press[i % 3]);
        i++;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    // shutdown sensor
    bme280spi.Shutdown();

    // Change the state to ready to sleep
    change_state(Sensor::State::READY_TO_SLEEP);

    // Sleep for the interval
}