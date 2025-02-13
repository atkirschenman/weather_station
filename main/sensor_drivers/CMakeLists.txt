add_subdirectory(bme280)
add_subdirectory(sensor_helpers)

add_library(sensor_drivers)
target_link_libraries(sensor_drivers PUBLIC bme280 sensor_helpers)
