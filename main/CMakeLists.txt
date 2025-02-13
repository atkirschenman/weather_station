idf_component_register(SRCS "weather_station.cpp"
                    INCLUDE_DIRS ".")

add_subdirectory(interface_drivers)
add_subdirectory(sensor_drivers)

add_executable(my_executable main.cpp)

# Link interface_drivers and sensor_drivers to main
target_link_libraries(my_executable PRIVATE interface_drivers sensor_drivers)