#include "wind_speed.hpp"
#include <chrono>
#include <mutex>
#include <queue>

#ifdef ARDUINO
QueueHandle_t queue; // Queue to store the time of the interrupts
#else
std::queue<unsigned long> queue;
std::mutex queue_mutex;
#endif

WindSpeed::WindSpeed(uint8_t pin) : sensorPin(pin)
{
}

void WindSpeed::begin()
{
#ifdef ARDUINO
    queue = xQueueCreate(1, sizeof(unsigned long));
    pinMode(sensorPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(sensorPin), handleInterrupt, FALLING);
#endif
}

float WindSpeed::get_wind_speed()
{
    return get_rpm_from_queue();
}

void WindSpeed::mock_handle_interupt(unsigned long time)
{
    send_to_queue(time);
}

uint32_t WindSpeed::get_millis()
{
#ifdef ARDUINO
    return millis();
#else
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    return duration.count();
#endif
}

float WindSpeed::get_rpm_from_queue()
{
    uint32_t queue_out = 0;
#ifdef ARDUINO
    auto size = uxQueueMessagesWaiting(queue);
    for (int i = 0; i <= size; i++)
    {
        auto temp = 0;
        xQueueReceive(queue, &temp, 0);
        queue_out += temp;
    }
#else
    auto size = queue.size();
    std::lock_guard<std::mutex> lock(queue_mutex);
    for (int i = 0; i <= size; i++)
    {
        queue_out += queue.front();
        queue.pop();
    }
#endif

    return (static_cast<float>(size) / static_cast<float>(queue_out)) * 60000.0;
}

void WindSpeed::send_to_queue(uint32_t num)
{
#ifdef ARDUINO
    xQueueSendFromISR(queue, &num, NULL);
#else
    std::lock_guard<std::mutex> lock(queue_mutex);
    queue.push(num);
#endif
}

#ifdef ARDUINO
void IRAM_ATTR WindSpeed::handle_interrupt()
{
    send_to_queue(get_millis());
}
#endif