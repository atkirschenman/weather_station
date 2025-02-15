#include "wind_direction.hpp"

WindDirection::WindDirection(uint8_t address) : address(address)
{
}

void WindDirection::begin()
{
    mcp.begin(address);
    for (int i = 0; i < 8; i++)
    {
        mcp.pinMode(i, INPUT);
        mcp.pullUp(i, HIGH);
    }
}

uint8_t WindDirection::getDirection()
{
    uint8_t direction = 0;
    for (int i = 0; i < 8; i++)
    {
        if (mcp.digitalRead(i) == LOW)
        {
            direction = i;
            break;
        }
    }
    return direction;
}
