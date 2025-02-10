# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/andrew/esp/esp-idf/components/bootloader/subproject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andrew/Documents/weather_station/build/bootloader

# Utility rule file for merge-bin.

# Include any custom commands dependencies for this target.
include CMakeFiles/merge-bin.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/merge-bin.dir/progress.make

CMakeFiles/merge-bin: bootloader
	cd /home/andrew/esp/esp-idf/components/esptool_py && /usr/bin/cmake -D IDF_PATH=/home/andrew/esp/esp-idf -D "SERIAL_TOOL=/home/andrew/.espressif/python_env/idf5.5_py3.12_env/bin/python;;/home/andrew/esp/esp-idf/components/esptool_py/esptool/esptool.py;--chip;esp32" -D "SERIAL_TOOL_ARGS=merge_bin;-o;/home/andrew/Documents/weather_station/build/bootloader/merged-binary.bin;@/home/andrew/Documents/weather_station/build/bootloader/flash_args" -D WORKING_DIRECTORY=/home/andrew/Documents/weather_station/build/bootloader -P run_serial_tool.cmake

merge-bin: CMakeFiles/merge-bin
merge-bin: CMakeFiles/merge-bin.dir/build.make
.PHONY : merge-bin

# Rule to build all files generated by this target.
CMakeFiles/merge-bin.dir/build: merge-bin
.PHONY : CMakeFiles/merge-bin.dir/build

CMakeFiles/merge-bin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/merge-bin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/merge-bin.dir/clean

CMakeFiles/merge-bin.dir/depend:
	cd /home/andrew/Documents/weather_station/build/bootloader && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrew/esp/esp-idf/components/bootloader/subproject /home/andrew/esp/esp-idf/components/bootloader/subproject /home/andrew/Documents/weather_station/build/bootloader /home/andrew/Documents/weather_station/build/bootloader /home/andrew/Documents/weather_station/build/bootloader/CMakeFiles/merge-bin.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/merge-bin.dir/depend

