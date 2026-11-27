cmake_minimum_required(VERSION 3.10)
project(cloud_chamber)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main main.cpp
	image.cpp
	calibration.cpp
)
