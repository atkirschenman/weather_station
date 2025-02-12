#!/bin/bash

# Set ESP-IDF installation path
ESP_IDF_DIR=~/esp/esp-idf

# Ensure ESP-IDF is sourced
if [ -f "$ESP_IDF_DIR/export.sh" ]; then
    source "$ESP_IDF_DIR/export.sh"
else
    echo "ESP-IDF is not installed. Run setup.sh first."
    exit 1
fi

# Build the project
echo "Building the ESP32-WROOM project..."
idf.py build

# Flash the firmware
#echo "Flashing firmware..."
#idf.py flash monitor
