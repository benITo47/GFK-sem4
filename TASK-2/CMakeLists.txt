cmake_minimum_required(VERSION 3.20)

# Project Name and Languages Used
project(lab2 VERSION 1.0 LANGUAGES CXX)

# Prevent for in-source building
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(SEND_ERROR "In-source builds are not allowed.")
endif ()

# Specify the C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the release type (debugging + symbols + warnings)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Wextra")

# Include directory for header files
set(INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDES})

# Set SFML include and library directories
set(SFML_INCLUDE_DIR "/opt/homebrew/Cellar/sfml/2.6.1/include")
set(SFML_LIBRARY_DIR "/opt/homebrew/Cellar/sfml/2.6.1/lib")

# Add SFML libraries manually
find_library(SFML_GRAPHICS_LIBRARY sfml-graphics PATHS ${SFML_LIBRARY_DIR})
find_library(SFML_WINDOW_LIBRARY sfml-window PATHS ${SFML_LIBRARY_DIR})
find_library(SFML_SYSTEM_LIBRARY sfml-system PATHS ${SFML_LIBRARY_DIR})
find_library(SFML_AUDIO_LIBRARY sfml-audio PATHS ${SFML_LIBRARY_DIR})

# Add the executable
add_executable(${PROJECT_NAME} main.cpp
        src/hexagon.cpp
        src/hexagon_RGB.cpp
        src/hexagon_HSL.cpp
        src/hexagon_HSB.cpp
        src/hexagon_CMY.cpp
        src/slider.cpp
)

# Link the executable with the SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
        ${SFML_GRAPHICS_LIBRARY}
        ${SFML_WINDOW_LIBRARY}
        ${SFML_SYSTEM_LIBRARY}
        ${SFML_AUDIO_LIBRARY}
)
