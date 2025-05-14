cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(uv5Gripper)
set(CMAKE_CXX_STANDARD 11)

add_executable(uv5Gripper functions.cpp functions.hpp Gripper.cpp Gripper.hpp main.cpp)
target_link_libraries(uv5Gripper PUBLIC pigpio)