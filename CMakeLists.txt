cmake_minimum_required(VERSION 3.10)
project(cloud_chamber)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#needed for SFML
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#SFML
set(BUILD_SHARED_LIBS ON)
set(SFML_BUILD_AUDIO OFF)
set(SFML_BUILD_NETWORK OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main main.cpp
	image.cpp
	calibration.cpp
)

target_link_libraries(main PRIVATE SFML::Graphics)

if(WIN32)
	add_custom_command(TARGET main POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:main> $<TARGET_FILE_DIR:main>
		COMMAND_EXPAND_LISTS)
endif()
