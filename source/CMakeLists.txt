cmake_minimum_required(VERSION 3.10.2)

project(RobotSim)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(Robot)

target_include_directories(${PROJECT_NAME} PUBLIC Robot)

link_directories(${PROJECT_NAME} PUBLIC Robot/)

target_link_libraries(${PROJECT_NAME} Robot)
