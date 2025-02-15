#pragma once
#ifdef ARDUINO
#include <Arduino.h>
#include <FreeRTOS.h>
#include "queue.h"
#endif
#include <cstdint>

class WindSpeed
{
  public:
    WindSpeed(uint8_t pin);
    void begin();
    float get_wind_speed();

  private:
    float get_rpm_from_queue();
    void send_to_queue(uint32_t num);
    uint32_t get_millis();
    uint8_t sensorPin;
    unsigned long lastTime;

#ifdef ARDUINO
  private:
    static void IRAM_ATTR handleInterrupt();
#else
  public:
    void mock_handle_interupt(unsigned long time);
#endif
};
