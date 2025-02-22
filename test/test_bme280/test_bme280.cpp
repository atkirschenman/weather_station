#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <Wire.h>
#include <cmath>
#include <gtest/gtest.h>
#include <string>
#include "Arduino.h"
#include "bme280.hpp"

// Mock class for BME280
class MockBME280 : public Adafruit_BME280
{
  public:
    MOCK_METHOD(float, readTemperature, (), (override));
    MOCK_METHOD(float, readHumidity, (), (override));
    MOCK_METHOD(float, readPressure, (), (override));
};

class BME280Test : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        bme280 = new BME280("test_sensor", 1000);
    }

    void TearDown() override
    {
        delete bme280;
    }

    BME280* bme280;
    MockBME280 mockBME280;
};

TEST_F(BME280Test, SensorInitializationFailure)
{
    EXPECT_CALL(mockBME280, begin(0x76)).WillOnce(::testing::Return(false));
    testing::internal::CaptureStderr();
    bme280->sensor_function();
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_NE(output.find("Could not find a valid BME280 sensor, check wiring!"),
              std::string::npos);
}

TEST_F(BME280Test, SensorReadsDataCorrectly)
{
    EXPECT_CALL(mockBME280, begin(0x76)).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockBME280, readTemperature()).WillOnce(::testing::Return(25.0));
    EXPECT_CALL(mockBME280, readHumidity()).WillOnce(::testing::Return(50.0));
    EXPECT_CALL(mockBME280, readPressure()).WillOnce(::testing::Return(1013.25));

    bme280->sensor_function();

    // Add assertions to check if the sensor data is read and sent correctly
    // This part depends on how Sensor.send_sensor_data is implemented
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}