cmake_minimum_required(VERSION 3.10)
project(cloud_chamber)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#needed for SFML
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/packages/SFML-3.1.0/lib/cmake/SFML")
find_package(SFML 3 REQUIRED COMPONENTS Graphics)

add_executable(main.exe main.cpp
	image.cpp
	calibration.cpp
)

target_link_libraries(main.exe PRIVATE SFML::Graphics)
