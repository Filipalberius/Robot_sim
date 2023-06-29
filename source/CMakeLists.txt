cmake_minimum_required(VERSION 3.10.2)

project(RobotSim)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(Robot)

link_directories(${PROJECT_NAME} PRIVATE Robot/)

target_link_libraries(${PROJECT_NAME} Robot)
