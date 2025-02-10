# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/andrew/esp/esp-idf/components/bootloader/subproject"
  "/home/andrew/Documents/weather_station/build/bootloader"
  "/home/andrew/Documents/weather_station/build/bootloader-prefix"
  "/home/andrew/Documents/weather_station/build/bootloader-prefix/tmp"
  "/home/andrew/Documents/weather_station/build/bootloader-prefix/src/bootloader-stamp"
  "/home/andrew/Documents/weather_station/build/bootloader-prefix/src"
  "/home/andrew/Documents/weather_station/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/andrew/Documents/weather_station/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/andrew/Documents/weather_station/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
