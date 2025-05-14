cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(uv5Gripper)
set(CMAKE_CXX_STANDARD 11)

add_executable(uv5Gripper main.cpp Gripper.cpp functions.cpp)
target_link_libraries(uv5Gripper PUBLIC pigpio)