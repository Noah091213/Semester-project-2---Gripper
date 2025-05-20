cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(uv5Gripper)
set(CMAKE_CXX_STANDARD 11)

include_directories(/usr/include)
link_directories(/usr/lib)

add_executable(uv5Gripper functions.cpp functions.hpp Gripper.cpp Gripper.hpp main.cpp)

find_package(SQLite3 REQUIRED)
target_link_libraries(uv5Gripper PUBLIC SQLite::SQLite3)
target_link_libraries(uv5Gripper PUBLIC pigpio)
target_link_libraries(uv5Gripper PUBLIC modbus)
