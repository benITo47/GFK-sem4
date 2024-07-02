cmake_minimum_required(VERSION 3.27)
project(Lab06)

set(CMAKE_CXX_STANDARD 17)

set(wxWidgets_ROOT_DIR </Users/bartek/wxWidgets-3.2.4/buildOSX>)
#set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

# Automatically collect all .cpp files from the src/ directory
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

# Automatically collect all .h files from the include/ directory
file(GLOB_RECURSE HEADER_FILES include/*.h)

# Add the include/ directory to the project include directories
include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES}
        main.cpp)

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
