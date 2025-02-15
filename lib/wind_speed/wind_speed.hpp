#pragma once

#include <Arduino.h>

class WindSpeed
{
  public:
    WindSpeed(uint8_t pin);
    void begin();
    float getWindSpeed();

  private:
    static void IRAM_ATTR handleInterrupt();
    uint8_t sensorPin;
    unsigned long lastTime;
};
