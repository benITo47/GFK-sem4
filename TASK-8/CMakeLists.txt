cmake_minimum_required(VERSION 3.27)
project(Lab08)

set(CMAKE_CXX_STANDARD 17)

# Find wxWidgets
set(wxWidgets_ROOT_DIR </Users/bartek/wxWidgets-3.2.4/buildOSX>)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

# Include directories
include_directories(include)

# Find FreeImage
find_library(FREEIMAGE_LIBRARY FreeImage PATHS /path/to/freeimage/lib)

# Find X11 if using CImg for display (on macOS, make sure XQuartz is installed)
find_package(X11 REQUIRED)

# Collect all .cpp and .h files
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.h)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES} main.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${FREEIMAGE_LIBRARY} ${X11_LIBRARIES})
find_package(JPEG REQUIRED)
include_directories(${JPEG_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${JPEG_LIBRARIES})


