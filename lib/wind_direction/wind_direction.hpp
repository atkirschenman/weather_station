#pragma once

#include <Adafruit_MCP23017.h>
#include <Wire.h>

class WindDirection
{
  public:
    WindDirection(uint8_t address);
    void begin();
    uint8_t getDirection();

  private:
    Adafruit_MCP23017 mcp;
    uint8_t address;
};
