#!/bin/bash

# Set ESP-IDF installation path
ESP_IDF_DIR=~/esp/esp-idf

# Check if ESP-IDF is already installed
if [ ! -d "$ESP_IDF_DIR" ]; then
    echo "Cloning ESP-IDF repository..."
    git clone --recursive https://github.com/espressif/esp-idf.git "$ESP_IDF_DIR"
    cd "$ESP_IDF_DIR" || exit
    ./install.sh
else
    echo "ESP-IDF is already installed."
fi

# Load ESP-IDF environment variables
echo "Setting up ESP-IDF environment..."
source "$ESP_IDF_DIR/export.sh"

# Set target to ESP32 (WROOM)
idf.py set-target esp32

echo "Setup complete. You can now build and flash your ESP32-WROOM project."
