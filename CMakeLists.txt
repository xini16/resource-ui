cmake_minimum_required(VERSION 3.5)

project(Box)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(ui main.cpp ResourceViewUI.cpp ResourceManager.cpp Resource.cpp MenuBarUI.cpp)

target_link_libraries(ui Qt6::Widgets)
