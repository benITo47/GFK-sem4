cmake_minimum_required(VERSION 3.27)
project(Lab03)

set(CMAKE_CXX_STANDARD 17)

set(wxWidgets_ROOT_DIR </Users/bartek/wxWidgets-3.2.4/buildOSX>)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base  REQUIRED)
include(${wxWidgets_USE_FILE})

set(SOURCE_FILES main.cpp
        MyFrame.cpp
        MonkeyPanel.cpp
)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})