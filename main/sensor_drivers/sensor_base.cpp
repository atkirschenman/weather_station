#include "sensor_base.hpp"

static void main_sensor_task(void *pvParameters)
{
    SensorBase *sensor = (SensorBase *)pvParameters;
    sensor->sensor_function();
    xtaskDelete(NULL);
}