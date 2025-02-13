add_library(bme280 bme280_common.cpp bme280_driver.cpp)
target_include_directories(bme280 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
