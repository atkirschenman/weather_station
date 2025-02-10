#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "FreeRTOS_Main";

void example_task(void *pvParameter) {
    while (1) {
        ESP_LOGI(TAG, "Task running...");
        vTaskDelay(pdMS_TO_TICKS(1000));  // Delay for 1000ms
    }
}

extern "C" void app_main(void) {
    ESP_LOGI(TAG, "Starting FreeRTOS Example...");
    xTaskCreate(example_task, "Example Task", 4096, NULL, 5, NULL);
}
