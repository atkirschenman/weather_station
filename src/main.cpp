#include <Arduino.h>
#include <chrono>
#include <esp_pthread.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include "esp_log.h"

static const char* TAG = "FreeRTOS_Main";

void example_task(void* pvParameter)
{
    while (1)
    {
        ESP_LOGI(TAG, "Task running...");
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000ms
    }
}

void setup()
{
    // put your setup code here, to run once:
    xTaskCreate(example_task, "example_task", 2048, NULL, 1, NULL);
}

void loop()
{
    // put your main code here, to run repeatedly:
    vTaskDelete(NULL);
}