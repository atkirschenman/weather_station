#ifdef ARDUINO
#include <Arduino.h>
#include <esp_pthread.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_log.h"
#else

#endif
#include <chrono>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <thread>

static const char* TAG = "FreeRTOS_Main";
std::thread main_thread;

void example_task(void* parameter)
{
    while (1)
    {
        std::cout << "task running" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Delay for 1 second
    }
}

void setup()
{
    // put your setup code here, to run once:
    main_thread = std::thread(example_task, nullptr);
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (main_thread.joinable())
    {
        main_thread.join();
    }
}