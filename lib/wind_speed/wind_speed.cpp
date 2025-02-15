#include "wind_speed.hpp"
#include <Arduino.h>
#include <FreeRTOS.h>
#include <queue.h>

QueueHandle_t queue; // Queue to store the time of the interrupts

WindSpeed::WindSpeed(uint8_t pin) : sensorPin(pin)
{
    queue = xQueueCreate(1, sizeof(unsigned long));
}

void WindSpeed::begin()
{
    pinMode(sensorPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(sensorPin), handleInterrupt, FALLING);
    lastTime = millis();
}
float WindSpeed::getWindSpeed()
{
    unsigned long currentTime;
    xQueueReceive(queue, &currentTime, portMAX_DELAY);
    float windSpeed = 1000.0 / (currentTime - lastTime);
    lastTime = currentTime;
    return windSpeed;
}
#ifdef ARDUINO
void IRAM_ATTR WindSpeed::handleInterrupt()
{
    xQueueSendFromISR(queue, &millis(), NULL);
}
#else
void WindSpeed::mock_handle_interrupt(unsigned long time)
{
    xQueueSendFromISR(queue, &time, NULL);
}
#endif
// Compare this snippet from test/test_wind_speed/test_wind_speed.cpp:

// #include "wind_speed.hpp"

// void test_wind_speed_initialization()

// {

//     WindSpeed sensor(2);

//     TEST_ASSERT_EQUAL(2, sensor.get_pin());

// }

// void test_wind_speed_sensor_function()

// {

//     WindSpeed sensor(2);

//     sensor.begin();

//     // Assuming we have some way to mock or check the sensor data

//     // For example, we could check if the wind speed is greater than 0

//     TEST_ASSERT_GREATER_THAN(0, sensor.getWindSpeed());

// }

// void test_wind_speed_handle_interrupt()

// {

//     WindSpeed sensor(2);

//     sensor.begin();

//     // Mocking the interrupt

//     sensor.handleInterrupt();

//     TEST_ASSERT_EQUAL(1, sensor.get_rotation_count());

// }

// void test_wind_speed_get_wind_speed()

// {

//     WindSpeed sensor(2);

//     sensor.begin();

//     // Mocking the interrupt

//     sensor.handleInterrupt();

//     // Assuming the wind speed is 10 m/s

//     TEST_ASSERT_EQUAL(10.0, sensor.getWindSpeed());

// }

// #ifdef ARDUINO

// void setup()

// {

//     UNITY_BEGIN();

//     RUN_TEST(test_add_function);

//     RUN_TEST(test_isEven_function);

//     RUN_TEST(test_wind_speed_initialization);

//     RUN_TEST(test_wind_speed_sensor_function);

//     RUN_TEST(test_wind_speed_handle_interrupt);

//     RUN_TEST(test_wind_speed_get_wind_speed);

//     UNITY_END();

// }
